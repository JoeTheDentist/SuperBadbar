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

bool Arg_Analyser::analyse(int argc, char *argv[]) 
{
	std::string str;
	for (int i = 1; i < argc; i++) {
		str = argv[i];
		if (str == "-no_trace") {
			_babar_trace_ = 0;
			_babar_constr_ = 0;
			_babar_perf_ = 0;
		} else if (str == "-record") {
			_babar_record_ = 1;
		} else if (str == "-replay") {
			_babar_replay_ = true;
			if (i + 1 == argc) {
				PRINT_DEBUG(1, "Erreur: argument manquant")
			} else {
				i = i + 1;
				_babar_replay_file_ = argv[i];
			}
		}
	}
	return true;
}

