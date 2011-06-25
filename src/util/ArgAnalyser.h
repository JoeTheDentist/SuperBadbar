/**
 * 	@file ArgAnalyser.h
 * 	@brief Header de la classe ArgAnalyser
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date 25/01/2011
 *
 */


/**
 * 	@class ArgAnalyser
 * 	@brief Analyse les arguments passés au main
 *
 *
**/

#include <string>


class ArgAnalyser {
public:
	//TODO
	ArgAnalyser(int argc, char *argv[]);
	~ArgAnalyser();
	bool arg_error();
	bool record_on();
	bool replay_on();
	bool menu_on();
	bool level_specified_on();
	std::string get_level_name();
	std::string input_file();
	std::string output_file();
private:
	bool m_arg_error;
	bool m_record_on;
	bool m_replay_on;
	bool m_menu;
	bool m_level_specified;
	std::string m_level_name;
	std::string m_input_file;
	std::string m_output_file;



};
