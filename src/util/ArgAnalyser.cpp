/**
 * 	@file ArgAnalyser.cpp
 * 	@brief Implémentation de la classe ArgAnalyser
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date 25/01/2011
 *
 */

#include <iostream>
#include "ArgAnalyser.h"
#include "debug.h"
#include <string>

ArgAnalyser::ArgAnalyser (int argc, char *argv[])
{
    m_arg_error = false;
    m_record_on = false;
    m_replay_on = false;
    m_menu = false;
    m_level_specified = false;
    std::string str;
    for (int i = 1; i < argc; i++)
    {
        str = argv[i];
        if (str == "-record")
        {
            m_record_on = true;
            m_output_file = "record.rcd";

        }
        else if (str == "-replay")
        {
            m_replay_on = true;
            if (i + 1 == argc)
            {
                PRINT_DEBUG (1, "Erreur: argument manquant")
                m_arg_error = true;
            }
            else
            {
                i = i + 1;
                m_input_file = argv[i];
            }
        }
        else if (str == "-menu")
        {
            m_menu = true;
        }
        else if (str == "-level")
        {
            if (i + 1 == argc)
            {
                PRINT_DEBUG (1, "Erreur: argument manquant")
                m_arg_error = true;
            }
            else
            {
                i = i + 1;
                m_level_name = argv[i];
                m_level_specified = true;
            }
        }
    }
}

ArgAnalyser::~ArgAnalyser()
{

}

bool ArgAnalyser::arg_error()
{
    return m_arg_error;
}
bool ArgAnalyser::record_on()
{
    return m_record_on;
}
bool ArgAnalyser::replay_on()
{
    return m_replay_on;
}
bool ArgAnalyser::menu_on()
{
    return m_menu;
}
bool ArgAnalyser::level_specified_on()
{
    return m_level_specified;
}
std::string ArgAnalyser::get_level_name()
{
    return m_level_name;
}
std::string ArgAnalyser::input_file()
{
    return m_input_file;
}
std::string ArgAnalyser::output_file()
{
    return m_output_file;
}
