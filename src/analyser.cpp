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
	m_current = fgetc(m_file);
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
	fseek(m_file, 0, SEEK_SET);
	while (m_current != EOF && char_found < size){
		if (m_current == str[char_found])
			char_found++;
		else
			char_found = 0;
		m_current = fgetc(m_file);
	}
	if (m_current !=EOF)
		m_current = fgetc(m_file);
}

void Analyser::jump_separators()
{
	bool jump = true;
	while (jump){
		switch (m_current){
		case ' ': case '\n':
			m_current = fgetc(m_file);
			break;
		case '/':
			m_current = fgetc(m_file);
			if (m_current != '/'){
				jump = false;
				break;
			}
			while (m_current != '\n')
				m_current = fgetc(m_file);
			break;
		default:
			jump = false;
			break;
		}
	}
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

void Analyser::read_monster(Monster *monster)
{
	uint32_t current = 0;


}

