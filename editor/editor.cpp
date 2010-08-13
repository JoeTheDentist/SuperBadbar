

#include <iostream>
#include <stdint.h>

#include "editor.h"    
#include "collision_matrix.h"
#include "window.h"

Editor::Editor()
{
	int choice = 0;
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
		std::cout << "Indiquez le chemin et le nom du fichier à créer" << std::endl;
		break;
	case 2:
		std::cout << "Indiquez le chemin et le nom du fichier à charger" << std::endl;
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