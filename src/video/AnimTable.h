/**
 * 	@file anim_manager.h
 * 	@brief Header de la classe AnimTable
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef ANIM_TABLE_H_INCLUDED
#define ANIM_TABLE_H_INCLUDED

#include <string>

#include "AnimPic.h"
#include "util/debug.h"

#define PICS_EXT ".png"

class Actor;
class Surface;

/**
 * 	@class AnimTable
 * 	@brief Automatise l'utilisation des animations
 *	@todo Finir la doc, et il y a un todo dans init_fire
 */
class AnimTable
{
private:
    char m_nb_states;           /* nombre d'etats de l'animation */
    int m_last_state;           /* dernier etat affiche, pour les changements d'animation */
    Direction m_last_dir;         /* dernier etat directionnelle */
    AnimPic * m_curr_anim;    /* pointeur sur l'animation courante */
    AnimPic ***m_anim;        /* tableau de pointeur vers les animations ; etat et gauche/droite */
    bool m_fire;                /* si il y a un etat de tir dans les animations */
    bool m_last_fire;

    /**
     * @brief TODO refaire !!!!!!!!!! Construction de l'animation pour un monstre ayant un etat de tir (2x plus d'images)
     */
    void init_fire (std::string anim_name);

    /**
     * @brief Construction de l'animation pour un monstre sans etat de tir
     */
    void init_nfire (std::string anim_name);

public:
    /**
     * @brief Constructeur intelligent, savant charger toutes les images propres au nom donne.
     *
     * A partir de la chaine de caractere : lien de l'image sans l'extension ni etat/dir, il sait
     * charger toutes les bonnes images... Check des fichier peut-etre un peu longs.
     * /!\\ Les num des images doivent correspondre a l'enum de l'etat correspondant...
     *
     *  @param string donnant l'adresse du paquet d'image a charger
     */
    AnimTable (std::string anim_name);

    /**
     * @brief Destructeur, liberation du tableau des animations.
     */
    virtual ~AnimTable();

    /**
     * @brief change l'animation courrante, en prenant en compte si l'animation est stoppable.
     */
    void change_anim (int s, Direction dir, bool fire = false , bool phase_rand = false);

    /**
     * @brief Accesseur a l'image courante de l'animation, l'image a afficher
     */
    Surface * curr_pic();

    /**
     *	Switch to the next picture
     */
    void next_pic();

    /**
     *  @brief Set hauteur et largeur en fonction de l'image courante
     *  @param Rect a modifier
     */
    void set_rect (Rect &pos);

    /**
     *	Sets the index of current image
     *	@param i: index
     */
    void set_img (int i);
};
#endif // ANIM_TABLE_H_INCLUDED
