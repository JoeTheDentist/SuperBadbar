/**
 * Classe sprite et ses héritiers: 
 * deplacements individuels des objets dynamiques
 **/

#ifndef _SPRITES_
#define _SPRITES_


/* directions */
#define DROITE 0
#define GAUCHE 1
#define HAUT 2
#define BAS 3

#define VITESSE_BABAR 10

class Sprite{
protected:
	SDL_Surface ** m_picture; 	/* tableau d'images du sprite */
	uint8_t m_nb_pictures; 		/* nombre d'images différentes */   // à garder?
	SDL_Rect m_pos; 		/* position du sprite et sa taille */
	SDL_Rect m_speed;		/* vitesse du sprite */
	bool m_cache;			/* afficher le sprite ou pas */
	uint8_t m_direction;		/* direction du sprite */
	uint8_t m_phase;		/* phase pour alterner les images lors du déplacememnt */
public:
	Sprite();			/* constructeur */
	virtual ~Sprite();		/* destructeur */
	void update_pos();		/* mise à jour de la position */
	SDL_Surface *current_picture(); /* accesseur */	// à modifier pour sélectionner la bonne image
	SDL_Rect position();		/* accesseur */
	uint32_t position_x(); 		/* accesseur */
	uint32_t position_y(); 		/* accesseur */
};


class Babar: public Sprite {
protected:
	
public:
	Babar();		/* constructeur */
	~Babar();		/* destructeur */
	void update_speed();	/* mise à jour de la vitesse en fonction des touches enfoncées */
};


class Monstre: public Sprite {	
protected:
	uint32_t m_type;		/* type de monstre */
	uint32_t m_area; 		/* taille de la zone d'allez-retour */
public:
	Monstre();
	Monstre(uint32_t type, SDL_Rect pos, uint32_t area);
	~Monstre();
	void update_speed();
	
};


#endif