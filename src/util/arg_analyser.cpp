/**
 * 	@file arg_analyser.cpp
 * 	@brief Implémentation de la classe Arg_Analyser
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date 25/01/2011
 *
 */

#include <iostream>
#include "arg_analyser.h"
#include "debug.h"
#include <string>

 Arg_Analyser::Arg_Analyser(int argc, char *argv[]) 
{
	m_arg_error = false;
	m_record_on = false;
	m_replay_on = false;
	std::string str;
	for (int i = 1; i < argc; i++) {
		str = argv[i];
		if (str == "-no_trace") { // TODO supprimer ou changer
			_babar_trace_ = 0;
			_babar_constr_ = 0;
			_babar_perf_ = 0;
		} else if (str == "-record") {
			_babar_record_ = 1; // TODO supprimer
			m_record_on = true;
			m_output_file = "record.rcd";
			
		} else if (str == "-replay") { // TODO supprimer
			_babar_replay_ = true;
			m_replay_on = true;
			if (i + 1 == argc) {
				PRINT_DEBUG(1, "Erreur: argument manquant")
				m_arg_error = true;
			} else {
				i = i + 1;
				_babar_replay_file_ = argv[i];
				m_input_file = argv[i];
			}
		}
	}
}

Arg_Analyser::~Arg_Analyser()
{
	
}

bool Arg_Analyser::arg_error()
{
	return m_arg_error;
}
bool Arg_Analyser::record_on()
{
	return m_record_on;
}
bool Arg_Analyser::replay_on()
{
	return m_replay_on;
}
std::string Arg_Analyser::input_file()
{
	return m_input_file;
}
std::string Arg_Analyser::output_file()
{
	return m_output_file;
}