#ifndef _INPUTSTRING_H_
#define _INPUTSTRING_H_


#include <list>
#include <string>

class EventKeyboard;

class InputString {
private:
	std::string m_string;
	std::list<std::string> m_previousStrings;
	int m_itPreviousStrings;

public:
	/*!
	*	@brief Constructeur
	*	@param str La chaine contenue dans l'InputString
	*/
	InputString(std::string str = "");

	/*!
	*	@brief Destructeur 
	*/
	~InputString() {}

	/*!
	*	@brief Met a jour la string en fonction de l'event
	*	@param event L'input clavier
	*/
	void treatEvent(const EventKeyboard &event);

	/*!
	*	@brief Accesseur
	*	@return La string contenue
	*/
	std::string getString() const {return m_string;}
	
	/*!
	*	@brief Mutateur
	*	@param str La nouvelle string
	*/	
	void setString(std::string str);
	
protected:
	void saveToUndoList();
	void undo();
	
	
	
	
	
};

#endif
