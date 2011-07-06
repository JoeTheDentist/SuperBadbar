/**
 * 	@file ListMenuActions.h
 * 	@brief Header de la classe SurfaceText
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date mars 2011
 *
 */

#ifndef _BABAR_LIST_MENU_ACTIONS_H_
#define _BABAR_LIST_MENU_ACTIONS_H_

#include <list>
#include <string>

#include "../control/Keyboard.h"

class Camera;
class MenuAction;
struct Rect;

/*!
*	@class ListMenuActions
*	@brief Represente une liste d'actions possibles au sein d'un menu, et permet de l'afficher
*
*	Quand la liste est non vide, elle possede toujours un element selectionne, qui peut etre modifie
*	par incr_curs et recupere par get_selected_action.
*
*	Cette liste sera mise a jour par une classe externe en fonction des actions du joueur. Elle ne sert
*	qu'a representer l'etat de la liste d'actions.
*/
class ListMenuActions {
	private:
	std::list<MenuAction*> m_actions;
	std::list<MenuAction *>::iterator m_iterator;

	public:
	/*!
	*	@brief Constructeur
	*/
	ListMenuActions();

	/*!
	*	@brief Destructeur
	*/
	~ListMenuActions();

	void update();

	void add_action(MenuAction *action);

	/*!
	*	@brief Ajoute a la liste une action classique (MenuActionClassic), a la fin des actions deja existantes
	*	@param action_name Le nom de l'action
	*	@param action_num Le numero de l'action
	*/
	void add_action_classic(std::string action_name, int action_num);

	/*!
	*	@brief Ajoute a la liste une action integer (MenuActionInteger), a la fin des actions deja existantes
	*	@param action_name Le nom de l'action
	*	@param action_num Le numero de l'action
	*	@param value La valeur contenue dans l'action integer
	*/
	void add_action_integer(std::string action_name, int action_num, int value);
	void add_action_keyconfig(std::string action_name, int action_num, std::string value, key k);

	/*!
	*	@brief Deplace le curseur pointant sur l'action selectionnee (et joue un son)
	*	@param dep Le deplacement du curseur (modulo le nombre d'actions)
	*/
	void incr_curs(int dep);
	/*!
	*	@brief Augmente la valeur (s'il y en a) de l'action courante (et joue un son)
	*	@param value Le deplacement de la valeur
	*/
	void incr_value(int value);

	void enter_pressed();

	/*!
	*	@brief Affiche a l'ecran les actions
	*	@param camera La camera chargee de de l'affichage
	*	@param pos La position du menu
	*/
	void display(Camera *camera, Rect pos) const; // NE PAS METTRE DE REFERENCE (effets de bord)

	/*!
	*	@brief Accesseur
	*	@return Le numero de l'action selectionnee
	*/
	int get_selected_action();

	int get_selected_action_value();

	/*!
	*	@brief Accesseur
	*	@return La largeur de la SurfaceText de la plus large action
	*/
	int width() const;

	/*!
	*	@brief Accesseur
	*	@return La somme des hautes des SurfaceText des actions
	*/
	int height() const;


}; // end class


#endif