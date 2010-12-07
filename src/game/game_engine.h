/**
 * Classe Game_engine: classe singleton qui permet de modifier ou d'obtenir les données
 * de la partie susceptibles de changer à chaque cycle de jeu.
 * Elle contient les listes de projectiles amies et ennemies, la liste des monstres à l'écran,
 * et la matrix des monstres du niveau.


 **/

#ifndef _DYNAMIC_DATA_
#define _DYNAMIC_DATA_

#include "../util/lists.h"
#include <stdint.h>

class Static_data;
class Game;
class Projectile;
class Monster;
class Camera;
class Sound_manager;
class Keyboard;
class Babar;

class Game_engine {
private:
	List<Projectile*> m_projectiles_friend;    	/* Liste des projectiles de Babar à l'écran */
	List<Projectile*> m_projectiles_ennemy;    	/* Liste des projectiles ennemis */
	List<Monster*> m_monsters;    				/* Liste des monsters dans l'écran */
	uint32_t m_matrix_weight;					/* Largeur de la matrice */
	uint32_t m_matrix_height;					/* Hauteur de la matrice */
	Sound_manager *m_sound_manager;
	Babar *m_babar;

public:
	Game_engine();			/* Constructeur */
	~Game_engine();/* Destructeur */
	void init_game_engine(Camera *camera, Static_data *static_data, Sound_manager *m_sound_manager, Keyboard *keyboard);
	bool projectiles_friend_end();									/* Retourne vrai quand on arrive à la fin de la liste des projectiles amis */
	void projectiles_friend_update_pos(Static_data *static_data);	/* MAJ la position des projectiles amis */
	void babar_update_pos(Static_data *static_data);
	void monsters_update_pos(Static_data *static_data);				/*MAJ la position des monstres */
	void babar_update_speed();
	void babar_update_state(Static_data *static_data);
	void babar_monsters_collision();
	void monsters_update_speed();									/*MAJ la vitesse des monstres */
	void display_monsters(Camera *camera);							/* Affiche les monstres à l'écran */
	void display_projectiles_friend(Camera *camera);				/* Affiche les projectiles amis */
	void delete_old_projectiles_friend(Static_data *static_data);
	void update_monsters_projectiles();
    void fill_monster_stats(uint32_t i, uint32_t j, uint32_t monster_type, uint32_t begin, uint32_t end, uint32_t life, bool fire, uint32_t speed,  Static_data *static_data);
    void update(Camera *m_camera);   /* Met à jour la listes des monstres et le tableau de monstres, gére les collisions */
	List<Projectile*> *projectiles_friend();						/* Accesseur sur la liste des projectiles amis */
	Babar *babar();

};



#endif
