
/**
 * La classe Pic_list contient une liste chainée d'images (avec leurs position dans le niveau et leur nom de fichier)
 * Elle permet de charger la liste à partir d'un fichier .lvl et de la sauvegarder dans un fichier .lvl 
 * Les méthodes permettent aussi d'ajouter un élément, de supprimer un élément sur lequel on a cliqué,
 * d'afficher l'ensemble des éléments de la liste, de retourner le dernier élément ou de retourner l'élément précédent un élément donné.
**/

#ifndef _PIC_LIST_
#define _PIC_LIST_

#include <iostream>
#include <stdint.h>
#include <SDL/SDL.h>

#include "window.h"

/**
 * Structure permettant la réalisation d'une liste chainée d'images positionnées dans le niveau
 * la surface de l'image est redondante avec son nom de fichier mais permet d'éviter de la recharger à chaque cycle
**/
struct pic_cell {
	SDL_Surface *pic;		/* image */
	SDL_Rect pos;			/* position de l'image */
	std::string pic_name;	/* chemin et nom de l'image */
	struct pic_cell *suiv;	/* élément suivant de la liste chainée */
};



class Pic_list{
private:
	pic_cell *m_list;		/* liste chainée d'images et de leurs informations */
public:
	Pic_list();										/* Constructeur par défaut (liste vide) */									
	Pic_list(std::string file_name);				/* Constructeur à partir du fichier file_name (au format .lvl) */	
	void save(FILE* file);							/* Sauvegarde  la liste dans un fichier .lvl file ouvert et en cours de sauvegarde */
	void add(std::string file_name, SDL_Rect pos);	/* Ajout d'un élément dans la liste. La surface est chargée à partir du nom de fichier */
	void display_list(Window *window);				/* Affichage (blittage sans raffraichissement) des images dans la caméra */
	void delete_pic(SDL_Rect pos);					/* Supprime la dernière image ajoutée en collision avec le point pos */
	pic_cell *last_pic_cell();						/* Accesseur: retourne la derniere pic_cell de la liste */
	pic_cell *previous_pic_cell(pic_cell *cell);	/* Accesseur: retourne la pic_cell précédent cell dans la liste. Si cell est la premiere, cell est retournée */
	pic_cell *next_pic_cell(pic_cell *cell);		/* Accesseur: retourne la pic_cell suivant cell dans la liste. Si cell est la dernière, cell est retournée */
	~Pic_list();									/* Destructeur */
	
	
};







#endif