#include <iostream>
#include <stdint.h>
#include <string>

#include "editor.h"


int main()
{
	std::string static_name;
	char choice;
	std::cout << "" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "********************" << std::endl;
	std::cout << "*Editeur de statics*" << std::endl;
	std::cout << "********************" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Que voulez-vous faire?" << std::endl; 
	std::cout << "1. Nouveau static" << std::endl;
	std::cout << "2. Charger static" << std::endl;
	std::cout << "Autre touche: Quitter" << std::endl;
	std::cin >> choice;
	switch(choice) {
		case '1':
			std::cout << "Entrez le nom du static à créer" << std::endl;
			std::cin >> static_name;
			if (!new_static_file(static_name)) 
				return 0;
			std::cout << static_name << std::endl;
			break;
		case '2':
			std::cout << "Entrez le nom du static à charger" << std::endl;
			std::cin >> static_name;
			std::cout << static_name << std::endl;
			break;
		default:
			return 0;
			break;
	}		
	Editor editor(static_name);
	editor.edit();
	
}