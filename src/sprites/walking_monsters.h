#ifndef _WALKING_MONSTERS_
#define _WALKING_MONSTERS_

#include "../sprites/monsters.h"

class Sound_manager;
class Analyser;

class Walking_monster : public Monster {
private:


public:
	Walking_monster(Sound_manager *sound_manager);
	Walking_monster(Sound_manager *sound_manager, Analyser *analyserLevel);
	~Walking_monster();
	void update_speed(Babar *babar);
};



#endif


