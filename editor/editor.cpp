

#include <iostream>
#include <stdint.h>
#include <string>

#include "editor.h"    
#include "collision_matrix.h"
#include "window.h"
#include "pic_list.h"

Editor::Editor()
{
	int choice = 0;
	size_t weight, height;
	std::string file_name;
	m_leave = false;
	while (choice < 1 || choice > 3){
		std::cout << "Editeur de niveaux SUPERBARAR" << std::endl;
		std::cout << "Que voulez-vous faire?" << std::endl;
		std::cout << "1. Nouveau niveau" << std::endl;
		std::cout << "2. Charger un niveau" << std::endl;
		std::cout << "3. Quitter" << std::endl;       
		std::cin >> choice;
	}
	switch (choice) {
	case 1:
		std::cout << "Indiquez le chemin/le nom du fichier à créer" << std::endl;
		std::cin >> file_name;
		std::cout << "Indiquez la largeur en pixels du niveau à créer" << std::endl;
		std::cin >> weight;
		std::cout << "Indiquez la hauteur en pixels du niveau à créer" << std::endl;
 		std::cin >> height;

		break;
	case 2:
		std::cout << "Indiquez le chemin/le nom du fichier à charger" << std::endl;
		std::cin >> file_name;
		break;
	case 3:
		m_leave = true;
		break;
	default:
		std::cout << "probleme dans le switch du constructeur de l'éditeur" << std::endl;
		break;
	}	
}

Editor::~Editor()
{
	
}