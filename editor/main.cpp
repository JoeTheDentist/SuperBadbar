#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "collision_matrix.h"
#include "editor.h"
#include "pic_list.h"
#include "files.h"



int main(int argc, char *argv[])
{
	//~ int choice = 0;
	//~ std::string file_name, background_name;
	//~ bool leave = false;
	
	//~ while (choice < 1 || choice > 4){
		//~ std::cout << "Editeur de niveaux SUPERBARAR" << std::endl;
		//~ std::cout << "Que voulez-vous faire?" << std::endl;
		//~ std::cout << "1. Nouveau niveau" << std::endl;
		//~ std::cout << "2. Charger un niveau" << std::endl;
		//~ std::cout << "3. Quitter" << std::endl;       
		//~ std::cout << "4. Défaut (pour les tests)" << std::endl;       
		//~ std::cin >> choice;
	//~ }
	//~ switch (choice) {
	//~ case 1:
		//~ std::cout << "Indiquez le chemin/le nom du fichier à créer" << std::endl;
		//~ std::cin >> file_name;
		//~ std::cout << "Indiquez le chemin/le nom du fond d'écran du niveau" << std::endl;
		//~ std::cin >> background_name;
		//~ new_level_file(file_name, background_name);
		//~ break;
	//~ case 2:
		//~ std::cout << "Indiquez le chemin/le nom du fichier à charger" << std::endl;
		//~ std::cin >> file_name;
		//~ break;
	//~ case 3:
		//~ leave = true;
		//~ break;                                                               

	//~ case 4:
		//~ file_name = "defaut";
		//~ break;
	//~ default:
		//~ std::cout << "probleme dans le switch du main.cpp de l'editeur" << std::endl;
		//~ break;
	//~ }
	//~ if (leave)
		//~ return 0;
	
	Editor editor("test.lvl");
	editor.edit();
	return 0;
}    
