/**
 * 	@file list_menu_actions.h
 * 	@brief Header de la classe Surface_text
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date mars 2011
 *
 */
  
#ifndef _BABAR_LIST_MENU_ACTIONS_H_
#define _BABAR_LIST_MENU_ACTIONS_H_

#include <list>
#include <string>

class Camera;
class Menu_action;
struct Rect;

/*!
*	@class List_menu_actions
*	@brief Represente une liste d'actions possibles au sein d'un menu, et permet de l'afficher
*
*	Quand la liste est non vide, elle possede toujours un element selectionne, qui peut etre modifie 
*	par incr_curs et recupere par get_selected_action.
*
*	Cette liste sera mise a jour par une classe externe en fonction des actions du joueur. Elle ne sert
*	qu'a representer l'etat de la liste d'actions.
*/
class List_menu_actions {
	private:
	std::list<Menu_action*> m_actions;
	std::list<Menu_action *>::iterator m_iterator;
	
	public:
	/*!
	*	@brief Constructeur
	*/
	List_menu_actions();
	
	/*!
	*	@brief Destructeur
	*/
	~List_menu_actions();
	
	/*!
	*	@brief Ajoute a la liste une action possible, a la fin des actions deja existantes
	*	@param action_name Le nom de l'action
	*	@param action_num Le numero de l'action
	*/
	void add_action(std::string action_name, int action_num);
	
	/*!
	*	@brief Deplace le curseur pointant sur l'action selectionnee (et joue un son)
	*	@param dep Le deplacement du curseur (modulo le nombre d'actions)
	*/
	void incr_curs(int dep);
	
	/*!
	*	@brief Affiche a l'ecran les actions
	*	@param camera La camera chargee de de l'affichage
	*	@param pos La position du menu
	*/
	void display(Camera *camera, Rect pos); // NE PAS METTRE DE REFERENCE (effets de bord)
	
	/*!
	*	@brief Accesseur
	*	@return Le numero de l'action selectionnee
	*/
	int get_selected_action();
	
	/*!
	*	@brief Accesseur
	*	@return La largeur de la Surface_text de la plus large action
	*/
	int width();
	
	/*!
	*	@brief Accesseur
	*	@return La somme des hautes des Surface_text des actions
	*/
	int height();
	
	
}; // end class


#endif
