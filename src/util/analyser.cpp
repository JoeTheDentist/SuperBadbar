#include <iostream>
#include <stdint.h>
#include <string>
#include <fstream>

#include "analyser.h"
#include "../util/debug.h"
#include "../video/statics.h"
#include "../game/static_data.h"
#include "../game/dynamic_data.h"
#include "../util/globals.h"


Analyser::Analyser()
{
	PRINT_CONSTR(2, "Construction d'un Analyser")
	m_opened = false;
	m_file = NULL;
}
Analyser::~Analyser()
{
	delete m_file;
   	PRINT_CONSTR(2, "Destruction d'un Analyser")
}

uint32_t Analyser::open(std::string file)
{
	m_file = new std::ifstream(file.c_str(), std::ios::in);
	if (m_file == NULL){
		PRINT_DEBUG(1, "Impossible d'ouvrir le fichier %s", file.c_str())
		return 1;
	}
	m_opened = true;
	return 0;
}

void Analyser::close()
{
	m_file->close();
	m_opened = false;
}

void Analyser::find_string(std::string str)
{
	uint32_t char_found = 0;
	uint32_t size = str.size();
	char current = '*';
	m_file->seekg(0);
	while (current != EOF && char_found < size){
		m_file->get(current);
		if (current == str[char_found])
			char_found++;
		else
			char_found = 0;
	}

}

bool Analyser::end_of_section()
{
	jump_separators();
	char temp = read_char();
	m_file->seekg(-1, ios::cur);
	return temp == '!';
}
                                      

void Analyser::jump_separators()
{
	char current;
	bool jump = true;
	while (jump){
		m_file->get(current);
		switch (current){
		case ' ': 
			PRINT_DEBUG(1, "espace ");
			break;
		case '\n':
			PRINT_DEBUG(1, "retour chariot ");
			break;
//~ 		case '/':
//~ 			m_file->get(current);
//~ 			if (current != '/'){
//~ 				jump = false;
//~ 				m_file->seekg(-1, ios::cur);
//~ 				break;
//~ 			}
//~ 			while (current != '\n') {
//~ 				m_file->get(current);
//~ 			}
//~ 			break;
		default:
			jump = false;
			break;
		}
	}
	m_file->seekg(-1, ios::cur);
}

int Analyser::read_int()
{
	int res;
	jump_separators();
	*m_file >> res;
	return res;
}

uint32_t Analyser::read_uint32_t()
{
	uint32_t res;
	jump_separators();
	*m_file >> res;
	return res;
}

std::string Analyser::read_string()
{
	jump_separators();
	std::string res;
	*m_file >> res;
	return res;
}

char Analyser::read_char()
{
	jump_separators();
	char res;
	*m_file >> res;
	return res;	
}

void Analyser::fill_statics(Static_data *static_data)
{
	std::string static_pic_rep = PIC_STATICS_R;
	std::string static_name;
    Rect pos;
	uint32_t x, y;
    find_string("#Statics#");
	*m_file >> static_name;
    while(static_name[0]!='!') {
        Static *curr_static;
		*m_file >> x;
		pos.x = x;
		*m_file >> y;
		pos.y = y;

        curr_static = new Static(static_pic_rep + static_name + PICS_EXT,pos);
		*m_file >> static_name;

		static_data->add_static(curr_static);
    }

}

void Analyser::fill_collision_matrix(uint32_t **matrix)
{
	std::string static_pic_rep = PIC_STATICS_R;
	uint32_t x, y, static_height, static_weight, temp;
	std::string static_name;
    find_string("#Statics#");
	*m_file >> static_name;
    while(static_name[0]!='!') {
		*m_file >> x >> y;
		std::ifstream static_file((static_pic_rep + static_name + COLL_EXT).c_str(), std::ios::in);
		static_file >> static_weight;
		static_file >> static_height;
		for (uint32_t j = y / BOX_SIZE ; j < y / BOX_SIZE + static_height; j++)
			for (uint32_t i = x / BOX_SIZE; i < x / BOX_SIZE + static_weight; i++) {
				static_file >> temp;
				matrix[i][j] |= temp; // oh un smiley
			}
            static_file.close();
            *m_file >> static_name;
		}
}

int Analyser::nb_monsters()
{
    int nb;
    find_string("#Monsters#");
	*m_file >> nb;
    return nb;
}

void Analyser::fill_monsters_pics(int nb_monsters, Static_data *static_data)
{
    /* A utiliser après nb_monster car il se place au bon endroit dans le fichier */
    std::string pic_monsters_rep = PIC_MONSTERS_R;
    std::string monster_name;
    for(int i = 0;i<2;i++) {
        for(int j = 0;j<3;j++) {
            for(int k=0;k<nb_monsters;k++) {
				*m_file >> monster_name;
                if(j==1) {
                    static_data->fill_monster_pic(i,3,k, (pic_monsters_rep+monster_name+PICS_EXT).c_str());
                }
                static_data->fill_monster_pic(i,j,k, (pic_monsters_rep+monster_name+PICS_EXT).c_str());
            }
        }
    }
}

void Analyser::fill_monsters(Analyser * analyser, Static_data *static_data, Dynamic_data *dynamic_data)
{
//~     /* Ici l'analyser en argument permet de traiter en parallèle deux bouts de fichiers sans ouvrir le fichier à chaque fois */
    uint32_t x,y,begin,end,life,speed,monster_type;
    bool fire;
    find_string("#PositionsMonstres#");
    while(!m_file->eof()) {
		*m_file >> monster_type >> x >> y >> begin >> end;
        analyser->fill_monsters_2(&life,&fire,&speed,monster_type);
        dynamic_data->fill_monster_stats(y/BOX_SIZE,x/BOX_SIZE,monster_type,begin,end,life,fire,speed, static_data);
    }
}

void Analyser::fill_monsters_2(uint32_t *life, bool *fire, uint32_t *speed, uint32_t type)
{
    char str[3];
    std::string str_type;
    sprintf(str, "%d", type);
    str_type = str;
	int temp;

    find_string("#"+str_type+"#");
	*m_file >> *life >> temp;
	*fire = temp & 1;
	*m_file >> *speed;
}
