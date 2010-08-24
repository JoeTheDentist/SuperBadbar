/**
 * La classe editor centralise la gestion des actions de l'utilisateur et délégue
 * les taches aux autres modules: 
 * 	- l'affichage au module window
 *	- la gestion des images à pic_list
 *	- la gestion de la matrice de collision à collision_matrix
 **/

#ifndef _EDITOR_
#define _EDITOR_

#include <iostream>
#include <stdint.h>
#include <SDL/SDL.h>

#include "collision_matrix.h"
#include "pic_list.h"
#include "window.h"

#define PIXELS_BEFORE_REFRESH 5

class Editor{
private:
	bool m_leave;							/* mis à faux lorsque l'utilisateur veut quitter */
	Window m_window;						/* fenetre de l'éditeur */
	Pic_list m_pic_list;					/* liste des images du niveau en cours */
	Collision_matrix m_collision_matrix;	/* matrice de collision du niveau en cours */
	std::string m_file_name;				/* nom du fichier du niveau en cours*/
	
	
public:
	Editor(std::string file_name);			/* constructeur à partir d'un fichier .lvl existant */
	void edit();							/* fonction principale de l'édition: boucle qui gère les actions de l'utilisateur jusqu'à ce qu'il quitte*/
	void refresh();							/* rafraichit la fenetre sans effectuer de flip*/
	void flip();							/* flip l'écran */
	void refresh_and_flip();				/* refresh et flip ^_^ */
	void save(std::string file_name);		/* sauvegarde le niveau édité dans un fichier au format .lvl*/
	void right_clic(int x, int y);			/* appelée pendant un clic droit: permet de se déplacer dans le niveau avec la souris */
	void shell();							/* appelée par la touche "t": permet d'accéder au terminal*/
	void insert_pic(std::string file_name);	/* insertion de l'image file_name: l'image est définitivement ajoutée avec un clic gauche */
	void insert_last_pic();					/* insertion de la derniere image de la liste m_pic_list*/
	void delete_pic();						/* appelée par "d": supprime de la liste m_pic_list la prochaine image cliquée */
	void leave_editor();					/* quitte l'éditeur */
	~Editor();								/* destructeur */
	
	
};



#endif