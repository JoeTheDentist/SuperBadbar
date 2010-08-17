#include <iostream>
#include <stdint.h>
#include <string>
#include "analyser.h"
#include "sprites.h"


Analyser::Analyser()
{
	m_opened = false;
	m_file = NULL;
}
Analyser::~Analyser()
{

}

uint32_t Analyser::open(std::string file)
{
	m_file = fopen(file.c_str(), "r");
	if (m_file == NULL)
		return 1;
	m_opened = true;
	return 0;
}

uint32_t Analyser::close()
{
	fclose(m_file);
	m_opened = false;
	return 0;
}

void Analyser::find_string(std::string str)
{
	uint32_t char_found = 0;
	uint32_t size = str.size();
	char current = 'a';
	fseek(m_file, 0, SEEK_SET);
	while (current != EOF && char_found < size){
		current = fgetc(m_file);
		if (current == str[char_found])
			char_found++;
		else
			char_found = 0;

	}
}

void Analyser::jump_separators()
{
	char current;
	bool jump = true;
	while (jump){
		current = fgetc(m_file);
		switch (current){
		case ' ': case '\n':
			break;
		case '/':
			current = fgetc(m_file);
			if (current != '/'){
				jump = false;
				break;
			}
			while (current != '\n')
				current = fgetc(m_file);
			break;
		default:
			jump = false;
			break;
		}
	}
	fseek(m_file, -1, SEEK_CUR);
}

void Analyser::fill_statics()
{
    char link[40];
    SDL_Rect pos;

    find_string("#Statics#");

    fscanf(m_file,"%s",link);
    jump_separators();
    while(link[0]!='!') {
        Static *curr_static;
        fscanf(m_file,"%d",&pos.x);
        jump_separators();
        fscanf(m_file,"%d",&pos.y);
        jump_separators();

        curr_static = new Static(link,pos);
        fscanf(m_file,"%s",&link);
        jump_separators();

        statics.add(curr_static);
    }
}

int Analyser::nb_monsters()
{
    int nb;
    find_string("#Monsters#");
    fscanf(m_file,"%d",&nb);
    return nb;
}

void Analyser::fill_monsters_pics()
{
    char link[40];

    jump_separators();
    fscanf(m_file,"%s",link);
    jump_separators();
    while(link[0]!='!') {
        for(int i = 0;i<3;i++) {
            for(int j = 0;j<3;j++) {
                fscanf(m_file,"%s",&link);
                jump_separators();
            }
        }
    }
}

