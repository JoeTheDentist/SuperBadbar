
#include <iostream>
#include <stdint.h>
#include <string>

#include "statics.h"
#include "windows.h"
#include "editor.h"


Static::Static(std::string name) : m_name(name)
{
	FILE *file = fopen((STATICS_DIR + name + COLL_EXT).c_str(), "r");
	if (file == NULL) {
		std::cout << "Erreur: impossible de trouver le fichier " <<  STATICS_DIR + name + COLL_EXT << std::endl;
		return;
	}
	fscanf(file, "%d", &m_weight);
	fscanf(file, "%d", &m_height);
	m_collision_matrix = new uint32_t*[m_weight];
	for (uint32_t i = 0; i < m_weight; i++){
		m_collision_matrix[i] = new uint32_t[m_height];
		for (uint32_t j = 0 ; j < m_height; j++) 
			fscanf(file, "%d", &(m_collision_matrix[i][j]));
	}
	fclose(file);
}


Static::~Static()
{
	//~ for (uint32_t i = 0; i < m_height; i++) 
		//~ delete[] m_collision_matrix[i];
	//~ delete[] m_collision_matrix;
}


void Static::save()
{
	FILE *file = fopen((STATICS_DIR + m_name + COLL_EXT).c_str(), "w+");
	fprintf(file, "%d %d\n", m_weight, m_height);
	for (uint32_t i = 0; i < m_weight; i++){
		for (uint32_t j = 0 ; j < m_height; j++) 
			fprintf(file, "%d ", m_collision_matrix[i][j]);
		fprintf(file, "\n");
	}
	fclose(file);
}


void Static::display_static(Window *window)
{
	window->blit_background();
}


void Static::display_collisions(Window *window)
{                   
	for (uint32_t i = 0; i < m_weight; i++)
		for (uint32_t j = 0 ; j < m_height; j++) 
			display_square(window, i, j);
	window->flip_screen();
}


void Static::display_square(Window *window, uint32_t x, uint32_t y)
{
	window->blit_square(x * SQUARE_SIZE, y * SQUARE_SIZE, m_collision_matrix[x][y]);
}


void Static::update_square(uint32_t x, uint32_t y, uint32_t coll_type)
{
	m_collision_matrix[x][y] = coll_type;
}

void Static::reset()
{
	for (uint32_t i = 0; i < m_weight; i++)
		for (uint32_t j = 0; j < m_height; j++)
			m_collision_matrix[i][j] = NO_COLL;
}

bool new_static_file(std::string static_name)
{
	uint32_t weight = static_weight(static_name);
	uint32_t height = static_height(static_name);
	if (weight * height == 0){
		std::cout << "L'image "<< STATICS_DIR + static_name + PICS_EXT << " est introuvable, veuillez la créer avant d'éditer le static " << static_name << std::endl;
		return false;
	}
	FILE *file = fopen((STATICS_DIR + static_name + COLL_EXT).c_str(), "w+");
	fprintf(file, "%d %d\n", weight, height);
	for (uint32_t i = 0; i < height; i++){
		for (uint32_t j = 0; j < weight; j++)
			fprintf(file, "%d ", NO_COLL);
		fprintf(file, "\n");
	}
	fclose(file);
	return true;
}