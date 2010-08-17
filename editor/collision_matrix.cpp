
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string>

#include "collision_matrix.h"
#include "files.h"

Collision_matrix::Collision_matrix()
{
	m_height = 0;
	m_weight = 0;
	m_matrix = NULL;
}

Collision_matrix::Collision_matrix(size_t weight, size_t height)
{
	m_weight = weight;
	m_height = height;
	m_matrix = new uint32_t*[weight];
	for (uint32_t i = 0; i < weight; i++)
		m_matrix[i] = new uint32_t[height];
	for (uint32_t i = 0; i < m_weight; i++)
		for (uint32_t j = 0; j < m_height; j++)
			m_matrix[i][j] = 0;
}


Collision_matrix::Collision_matrix(std::string file_name)
{
	FILE* file = fopen(file_name.c_str(), "r");
	find_string("Size:", file);
	fscanf(file, "%d", &m_weight);
	fscanf(file, "%d", &m_height);
	fprintf(stderr, "%d %d\n", m_weight, m_height);
	
	m_matrix = new uint32_t*[m_weight];
	find_string("Collision:", file);
	for (uint32_t i = 0; i < m_weight; i++)
		m_matrix[i] = new uint32_t[m_height];
	for (uint32_t i = 0; i < m_weight; i++) {
		for (uint32_t j = 0; j < m_height; j++) 
			fscanf(file, "%u", m_matrix[i] + j * sizeof(uint32_t));
	}
			
	fclose(file);
}                                       


Collision_matrix::~Collision_matrix()
{
	for (uint32_t i = 0; i < m_weight; i++)
		delete[] m_matrix[i];
	delete[] m_matrix;
	m_matrix = NULL;
}

void Collision_matrix::save(FILE *file)
{
	fprintf(file, "Collision:\n");			
	for (uint32_t i = 0; i < m_height; i++){
		for (uint32_t j = 0; j < m_weight; j++){
			fprintf(file, "%d ", m_matrix[i][j]);			
		}
		fprintf(file, "\n");
	
	}
}
