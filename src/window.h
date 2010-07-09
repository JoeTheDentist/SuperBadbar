/**
 * Gestion de la fenêtre principale
 **/

#ifndef _WINDOW_
#define _WINDOW_


/**
 * Ouvre une fenêtre avec la taille spécifiée
 **/
uint8_t open_window(uint16_t weight, uint16_t height);

/**
 * Pose le fond de la fenêtre
 **/
uint8_t fill_screen(char *picture);

/**
 * Ferme la fenêtre
 **/
void close_window();

#endif