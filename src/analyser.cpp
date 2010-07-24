#include <iostream>
#include <stdint.h>
#include <string>

#include "analyser.h"


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
	char current;
	uint32_t char_found = 0;
	uint32_t size = str.size();
	fseek(m_file, 0, SEEK_SET);
	current = fgetc(m_file);
	while (current != EOF && char_found < size){
		if (current == str[char_found])
			char_found++;
		else
			char_found = 0;
		current = fgetc(m_file);
	}
}

