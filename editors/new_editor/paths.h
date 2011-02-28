#ifndef _EDITOR_PATHS_H
#define	_EDITOR_PATHS_H

// definitions des chemins
#define STATIC_DIR "../../pic/statics/"
#define BACKGROUND_DIR "../../pic/backgrounds/"
#define MONSTERS_DIR "../../data/monsters/"
#define MONSTERS_PIC_DIR "../../pic/monsters/"


// dimensions de la camera du jeu (utiles pour calculer 
// du niveau en fonction de la taille du background)
#define CAMERA_WIDTH 800
#define CAMERA_HEIGHT 600

// niveaux de zbuffer
#define BACKGROUND_ZBUFFER 0
#define STATICS_0_ZBUFFER 1
#define STATICS_1_ZBUFFER 3
#define MONSTERS_ZBUFFER 2
#define BABAR_ZBUFFER 4

#endif
