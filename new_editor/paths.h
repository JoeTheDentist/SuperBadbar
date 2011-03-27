#ifndef _EDITOR_PATHS_H
#define	_EDITOR_PATHS_H


// definitions des chemins
#define STATIC_DIR "../pic/statics/"
#define BACKGROUND_DIR "../pic/backgrounds/"
#define MONSTERS_DIR "../data/monsters/"
#define MONSTERS_PIC_DIR "../pic/monsters/"
#define EVENTS_DIR "../data/events/"
#define LEVELS_DIR "../data/levels/"
#define EVENTS_PIC_DIR "../pic/events/"
#define BABAR_PIC_DIR "../pic/babar/"

#define EVENTS_EXT ".evt"

// dimensions de la camera du jeu (utiles pour calculer 
// du niveau en fonction de la taille du background)
#define CAMERA_WIDTH 800
#define CAMERA_HEIGHT 600

// niveaux de zbuffer
#define BACKGROUND_ZBUFFER 0
#define STATICS_0_ZBUFFER 1
#define MONSTERS_ZBUFFER 2
#define STATICS_1_ZBUFFER 3
#define EVENTS_ZBUFFER 4
#define BABAR_ZBUFFER 5

#endif
