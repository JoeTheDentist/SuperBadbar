
#include <math.h>
#include <sys/stat.h>

#include "globals.h"
#include "control/KeyboardConfig.h"

SoundEngine * gSound = NULL;
CollisionsManager * gCollision = NULL;
StaticData * gStatic = NULL;
ProjectilesManager * gProj = NULL;
EventsManager * gEvent = NULL;
//Babar * gBabar = NULL;
GraphicEngine * gGraphics = NULL;
GameEngine * gGameEngine = NULL;
Stats * gStats = NULL;
PlayersManager * gPlayers = NULL;
KeyboardConfig *gKeyboardConfig = NULL;
NetworkManager *gNetwork = NULL;


double dist(Rect A, Rect B)
{
	Rect mA = A;
	Rect mB = B;

	mA.x = mA.x+mA.w/2;
	mA.y = mA.y+mA.h/2;

	mB.x = mB.x+mB.w/2;
	mB.y = mB.y+mB.h/2;

	return sqrt( (mA.x-mB.x)*(mA.x-mB.x) + (mA.y-mB.y)*(mA.y-mB.y) );
}

bool FileExists(std::string strFilename) {
	struct stat stFileInfo;
	bool blnReturn;
	int intStat;

	// Attempt to get the file attributes
	intStat = stat(strFilename.c_str(),&stFileInfo);
	if(intStat == 0) {
		// We were able to get the file attributes
		// so the file obviously exists.
		blnReturn = true;
	} else {
		// We were not able to get the file attributes.
		// This may mean that we don't have permission to
		// access the folder which contains this file. If you
		// need to do that level of checking, lookup the
		// return values of stat which will give you
		// more details on why stat failed.
		blnReturn = false;
	}

	return(blnReturn);
}
