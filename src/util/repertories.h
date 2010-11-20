#ifndef _REPERTORIES_
#define _REPERTORIES_

#ifdef WIN32
    #define RACINE_R std::string("../")
#else
   #define RACINE_R std::string("../")
#endif


#define PIC_R RACINE_R + "pic/"
	#define PIC_BABAR_R 			PIC_R + "babar/"
	#define PIC_BACKGROUNDS_R		PIC_R + "backgrounds/"
	#define PIC_DASHBOARD_R			PIC_R + "dashboard/"
	#define PIC_EDITOR_R			PIC_R + "editor/"
	#define PIC_ITEMS_R				PIC_R + "items/"
	#define PIC_MONSTERS_R 			PIC_R + "monsters/"
	#define PIC_PROJ_R				PIC_R + "projectiles/"
	#define PIC_STATICS_R			PIC_R + "statics/"
	#define PIC_TALKS_R				PIC_R + "talks/"
#define LEVELS_R RACINE_R + "data/levels/"













#endif
