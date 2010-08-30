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
	if (m_file == NULL){
		std::cout << "impossible d'ouvrir le fichier " << file << std::endl;
		return 1;
	}
	m_opened = true;
	return 0;
}

uint32_t Analyser::close()
{
	fclose(m_file);
	m_file = NULL;
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
				fseek(m_file, -1, SEEK_CUR);
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
	std::string static_name;
    SDL_Rect pos;
	uint32_t x, y;
    find_string("#Statics#");
    fscanf(m_file,"%s",link);
	static_name = link;
    jump_separators();
    while(link[0]!='!') {
        Static *curr_static;
        jump_separators();		
        fscanf(m_file,"%d",&x);
        jump_separators();
        fscanf(m_file,"%d",&y);
        jump_separators();
		pos.x = x;
		pos.y = y;
        curr_static = new Static(STATICS_DIR + static_name + PICS_EXT,pos);
        fscanf(m_file,"%s",link);
		static_name = link;
        jump_separators();
        statics.add(curr_static);
    }

}

void Analyser::fill_collision_matrix(uint32_t **matrix)
{

	uint32_t x, y, static_height, static_weight, temp;
	char static_name[40];
    find_string("#Statics#");
    fscanf(m_file,"%s",static_name);
	std::string str = static_name;
    while(static_name[0]!='!') {
        fscanf(m_file,"%d",&x);
        fscanf(m_file,"%d",&y);
		FILE* static_file = fopen ((STATICS_DIR + str + COLL_EXT).c_str(), "r");
		fscanf(static_file, "%d", &static_weight);
		jump_separators();
		fscanf(static_file, "%d", &static_height);
		jump_separators();
		for (uint32_t j = y / BOX_SIZE ; j < y / BOX_SIZE + static_height; j++) 
			for (uint32_t i = x / BOX_SIZE; i < x / BOX_SIZE + static_weight; i++) {
				fscanf(static_file, "%d", &temp);
				jump_separators();
				matrix[i][j] |= temp; // oh un smiley
			}
		fclose(static_file);
        fscanf(m_file,"%s",static_name);
		str = static_name;
        jump_separators();
    }

	
}

int Analyser::nb_monsters()
{
    int nb;
    find_string("#Monsters#");
    fscanf(m_file,"%d",&nb);
    return nb;
}

void Analyser::fill_monsters_pics(int nb_monsters)
{
    /* A utiliser après nb_monster car il se place au bon endroit dans le fichier */
    char link[40];

    jump_separators();
    for(int i = 0;i<3;i++) {
        for(int j = 0;j<3;j++) {
            for(int k=0;k<3;k++) {
                for(int l=0;l<nb_monsters;l++) {
                    jump_separators();
                    fscanf(m_file,"%s",link);
                    curr_lvl.fill_monster_pic(i,j,k,l,link);
                }
            }
        }
    }
}

void Analyser::fill_monsters(Analyser * analyser)
{
    /* Ici l'analyser en argument permet de traiter en parallèle deux bouts de fichiers sans ouvrir le fichier à chaque fois */
    uint32_t x,y,begin,end,life,speed,monster_type;
    bool fire;
    find_string("#PositionsMonstres#");
    while(!feof(m_file)) {
        jump_separators();
        fscanf(m_file,"%d",&monster_type);
        fscanf(m_file,"%d",&x);
        fscanf(m_file,"%d",&y);
        fscanf(m_file,"%d",&begin);
        fscanf(m_file,"%d",&end);
        analyser->fill_monsters_2(&life,&fire,&speed,monster_type);
        curr_lvl.fill_monster_pos(y/BOX_SIZE,x/BOX_SIZE,monster_type,begin,end,life,fire,speed);
    }
}

void Analyser::fill_monsters_2(uint32_t *life, bool *fire, uint32_t *speed, uint32_t type)
{
    char str[3];
    std::string str_type;
    sprintf(str, "%d", type);
    str_type = str;

    find_string("#"+str_type+"#");
    fscanf(m_file,"%d",life);
    fscanf(m_file,"%d",fire);
    fscanf(m_file,"%d",speed);
}
