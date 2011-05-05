#ifndef _EDITOR_PATHS_H
#define	_EDITOR_PATHS_H


// definitions des chemins
#define SET_DIR "../pic/animations/"
#define STATIC_DIR "../pic/statics/"
#define BACKGROUND_DIR "../pic/backgrounds/"
#define MONSTERS_DIR "../data/monsters/"
#define MONSTERS_PIC_DIR "../pic/monsters/"
#define EVENTS_DIR "../data/events/"
#define LEVELS_DIR "../data/levels/"
#define EVENTS_PIC_DIR "../pic/events/"
#define BABAR_PIC_DIR "../pic/babar/"

#define EVENTS_EXT ".evt"
#define TRIGGERS_EXT ".trg"

// dimensions de la camera du jeu (utiles pour calculer 
// du niveau en fonction de la taille du background)
#define CAMERA_WIDTH 800
#define CAMERA_HEIGHT 600

// niveaux de zbuffer
#define BACKGROUND_ZBUFFER 0
#define STATICS_0_ZBUFFER 1
#define SET_ZBUFFER 2
#define MONSTERS_ZBUFFER 3
#define STATICS_1_ZBUFFER 4
#define EVENTS_ZBUFFER 5
#define TRIGGERS_ZBUFFER 6
#define BABAR_ZBUFFER 7

#endif
