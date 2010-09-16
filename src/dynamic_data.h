

#ifndef _DYNAMIC_DATA_
#define _DYNAMIC_DATA_

#include "keyboard.h"
#include "sprites.h"
#include "lists.h"
#include "camera.h"
#include "static_data.h"

class Static_data;
class Game;
class Projectile;
class Monster;
class Camera;

class Dynamic_data {
private:
	List<Projectile*> m_projectiles_friend;    /* liste des projectiles de Babar à l'écran */
	List<Projectile*> m_projectiles_ennemy;    /* liste des projectiles ennemis */
	List<Monster*> m_monsters;     /* Liste des monsters dans l'écran */
	Monster *** m_monsters_matrix;              /* Matrice de pointeurs des monstres */
	uint32_t m_matrix_weight;
	uint32_t m_matrix_height;

public:
	Dynamic_data();
	Dynamic_data(Camera *camera, Static_data *static_data);
	~Dynamic_data();
	bool projectiles_friend_end();
	void projectiles_friend_update_pos(Static_data *static_data);
	void monsters_update_pos(Static_data *static_data);
	void monsters_update_speed();
	void display_monsters(Camera *camera);
	void display_projectiles_friend(Camera *camera);
	void delete_old_projectiles_friend(Static_data *static_data);
	void update_monsters_projectiles();
	void fill_monster(uint32_t i, uint32_t j, Monster * monster);
    void fill_monster_stats(uint32_t i, uint32_t j, uint32_t monster_type, uint32_t begin, uint32_t end, uint32_t life, bool fire, uint32_t speed,  Static_data *static_data);
    void update(Camera *m_camera);   /* Met à jour la listes des monstres et le tableau de monstres, gére les collisions */
	List<Projectile*> *projectiles_friend();

	
};


bool to_kill(Monster * monster, List<Projectile*> *projectiles_friend);
bool check_monster_proj(Projectile * proj, Monster * monster);



#endif
