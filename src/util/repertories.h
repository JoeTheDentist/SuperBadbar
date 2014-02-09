/**
 * 	@file repertories.h
 * 	@brief Defines des chemins vers les données
 *
 *	On se repère par rapport �  la racine du projet
 *	Les chemins commencent tous par la racine
 *	Chaque chemin est un std::string
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */



#ifndef _REPERTORIES_
#define _REPERTORIES_

#ifdef WIN32
#define RACINE_R std::string("../")
#else
#define RACINE_R std::string("../")
#endif

#define RECORDS_R RACINE_R + "records/"
#define PIC_R RACINE_R + "res/pic/"
#define PIC_BABAR_R 			PIC_R + "babar/"
#define PIC_BACKGROUNDS_R		PIC_R + "backgrounds/"
#define PIC_DASHBOARD_R			PIC_R + "dashboard/"
#define PIC_EDITOR_R			PIC_R + "editor/"
#define PIC_EVENTS_R			PIC_R + "events/"
#define PIC_ITEMS_R				PIC_R + "items/"
#define PIC_MENU_R				PIC_R + "menus/"
#define PIC_MONSTERS_R 			PIC_R + "monsters/"
#define PIC_PROJ_R				PIC_R + "projectiles/"
#define PIC_STATICS_R			PIC_R + "statics/"
#define PIC_TALKS_R				PIC_R + "talks/"
#define PIC_MAINMENU_R			PIC_R + "mainmenu/"
#define PIC_TRANSITIONS_R		PIC_R + "transitions/"
#define PIC_ANIMATIONS_R        PIC_R + "animations/"
#define PIC_DEBUG_R				PIC_R + "debug/"
#define DATA_R RACINE_R + "res/data/"
#define CONFIG_R DATA_R + "config/"
#define LEVELS_R DATA_R + "levels/"
#define EVENTS_R DATA_R + "events/"
#define TALKS_R DATA_R + "talks/texts/"
#define FONTS_R DATA_R + "talks/fonts/"
#define MONSTERS_STATS_R DATA_R + "monsters/"
#define SOUNDS_R RACINE_R + "res/sound/"
#define MONSTERS_SOUNDS_R SOUNDS_R + "monsters/"
#define BABAR_SOUNDS_R SOUNDS_R + "babar/"
#define FIRE_SOUNDS_R SOUNDS_R + "fire/"
#define MENU_SOUNDS_R SOUNDS_R + "menu/"
#define MUSIC_R SOUNDS_R + "music/"



#define MONSTERS_EXT ".mstr"
#define SOUNDS_EXT ".mp3"
#define EVENTS_EXT ".evt"
#define PIC_EXT ".png"







#endif
