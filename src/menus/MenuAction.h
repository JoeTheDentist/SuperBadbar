#ifndef _BABAR_MENU_ACTION_H_
#define _BABAR_MENU_ACTION_H_

#include <string>
#include "../control/Keyboard.h"

class Surface;
class EventKeyboard;

class MenuAction {
	protected:
	Surface *m_surface_text;
	Surface *m_surface_text_selected;
	std::string m_text;
	std::string m_text_to_display;	// 
	int m_index; // numero du menuaction dans la liste

	bool m_selected; // vrai si le menu est selectionne
	int m_size_sup; // valeur qu'on ajoute a la taille de la police en fonction des interactions

	public:
	/*!
	*	@brief Constructeur
	*	@param str Intitule du bouton
	*	@param i Indice du bouton dans le menu
	*/
	MenuAction(std::string str, int i);

	/*!
	*	@brief Destructeur
	*/
	~MenuAction();

	/*!
	*	@brief Maj du bouton
	*/
	virtual void update();

	/*!
	*	@brief Accesseur
	*	@return L'indice du bouton dans le menu
	*/
	virtual int get_index() const { return m_index; }

	/*!
	*	@brief Accesseur
	*	@return La valeur entiere contenue par le bouton (0 si indéfinie)
	*/
	virtual int getValueInteger() const {return 0;}

	/*!
	*	@brief Selectionne le bouton
	*/
	virtual void select();
	
	/*!
	*	@brief Deselectionne le bouton
	*/
	virtual void deselect() {m_selected = false;}

	/*!
	*	@brief Accesseur
	*	@return La surface du bouton
	*/
	virtual Surface *get_surface() const;
	
	/*!
	*	@brief Accesseur
	*	@return La largeur de la surface du bouton
	*/
	virtual int width() const;

	/*!
	*	@brief Accesseur
	*	@return La hauteur de la surface du bouton
	*/
	virtual int height() const;

	/*!
	*	@brief Incremente la valeur entiere contenue par le bouton
	*
	*	N'a de sens que si le bouton contient une valeur entiere...
	*/
	virtual void incr_value(int value);
		
	/*!
	*	@brief Accesseur
	*	@return La valeur string contenue dans le bouton ("" si indéfinie)
	*/
	virtual std::string get_string() const {return "";}
	
	virtual void treatEvent(EventKeyboard *eventKeyboard);


protected:
	virtual void update_text();
	virtual void update_pic(std::string str);
};


#endif
