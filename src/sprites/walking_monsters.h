#ifndef _WALKING_MONSTERS_
#define _WALKING_MONSTERS_

#include "../sprites/monsters.h"

class Pictures_container;
class Sound_manager;
class Analyser;

class Walking_monster : public Monster {
private:


public:
	Walking_monster(Sound_manager *sound_manager);
	Walking_monster(Sound_manager *sound_manager, Analyser *analyserLevel, Pictures_container *pictures_container);
	~Walking_monster();
	void update_speed(Babar *babar);
};



#endif


