/**
 * 	@file analyser.cpp
 * 	@brief Implémentation de la classe Analyser
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
 
#include <iostream>
#include <stdint.h>
#include <string>
#include <fstream>

#include "Analyser.h"
#include "../util/debug.h"
#include "../util/globals.h"


Analyser::Analyser()
{
	PRINT_CONSTR(3, "Construction d'un Analyser")
	m_opened = false;
	m_file = NULL;
}

Analyser::~Analyser()
{
   	PRINT_CONSTR(3, "Destruction d'un Analyser")
}

uint32_t Analyser::open(std::string file)
{
	m_filename = file;
	PRINT_TRACE(3, "Ouverture du fichier %s", file.c_str())
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
	PRINT_TRACE(3, "Fermeture du fichier %s", m_filename.c_str())	
	m_file->close();
	delete m_file;
	m_opened = false;
}

bool Analyser::find_string(std::string str)
{
	m_file->seekg(0);
	return find_next_string(str);
}

bool Analyser::find_next_string(std::string str)
{
	uint32_t char_found = 0;
	uint32_t size = str.size();
	char current = '*';
	while (!m_file->eof() && char_found < size){
		m_file->get(current);
		if (current == str[char_found])
			char_found++;
		else
			char_found = 0;
	}
	return char_found == size;	
}

bool Analyser::end_of_section()
{
	char temp = read_char();
	m_file->seekg(-1, std::ios::cur);
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
			break;
		case '\n':
			break;
//~ 		case '/':
//~ 			m_file->get(current);
//~ 			if (current != '/'){
//~ 				jump = false;
//~ 				m_file->seekg(-1, std::ios::cur);
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
	m_file->seekg(-1, std::ios::cur);
}

int Analyser::read_int()
{
	int res;
//~ 	jump_separators();
	*m_file >> res;
	return res;
}

uint32_t Analyser::read_uint32_t()
{
	uint32_t res;
//~ 	jump_separators();
	*m_file >> res;
	return res;
}

std::string Analyser::read_string()
{
	std::string res;
	*m_file >> res;
	return res;
}

std::string Analyser::read_between_char(char delimitor)
{
	std::string res;
	char current_char = ' ';
	while (current_char != delimitor) {
		m_file->get(current_char);
	}
	m_file->get(current_char);
	while (current_char != delimitor) {
		res += current_char;
		m_file->get(current_char);
	}
	return res;
}


char Analyser::read_char()
{
	jump_separators();
	char res;
	*m_file >> res;
	return res;	
}

void Analyser::push_curs()
{
	m_curs_stack.push(m_file->tellg());
}

void Analyser::pop_curs()
{
	m_file->seekg(m_curs_stack.top(), std::ios::beg);
	m_curs_stack.pop();
}
