/**
 * 	@file BindablePlatform.h
 * 	@brief header de la classe BindablePlatform
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date avril 2011
 *
 */

#ifndef _BINDABLE_PLATFORM_
#define _BINDABLE_PLATFORM_

#include <string>
#include <stdint.h>

#include "video/Statics.h"
#include "util/debug.h"
#include "util/Analyser.h"
#include "physic/CollisionsMatrix.h"

class Surface;
class Babar;
class Camera;

/**
 * 	@class BindablePlatform
 * 	@brief Classe repr√©sentant une plateforme de collision potentiellement mobile
 *
 *	Elle peut etre affich√©e, se d√©place et contient des donn√©es de collision
 *	Babar est le seul sprite en int√©raction avec la plateforme.
 *	Lorsque Babar tombe sur la plateforme, il est li√©e √  elle
 *	Dans ce cas, il suit ses d√©placements jusqu'√  son prochain son
 * 	ou sa chute de la plateforme. La plateforme "sait" si elle est li√©e
 *	ou pas √  Babar.
 *	Une plateforme mobile est construite √  partir du meme type de fichier qu'un
 *	static: un .col pour la matrice de collisions et une image
 */
class BindablePlatform : public Static, public CollisionsMatrix
{
protected:
    Babar *m_babar;
    Rect m_speed;
    int m_phase;
    int m_can_bind;
public:

    /**
     * 	@brief Constructeur
     */
    BindablePlatform();

    /**
     * 	@brief Destructeur
     */
    virtual ~BindablePlatform();

    /**
     * 	@brief Initialise le BindablePlatform
     *	@param posx La position x du bindable
     *	@param posy La position y du bindable
     *	@param file_name Le nom du fichier depuis les statics
     */
    void init_bindable_platform (int posx, int posy, std::string file_name);

    /**
     * 	@brief Mise √  jour de la position
     *	@param babar Un personnage controle par le joueur
     *
     *	Detecte la collision avec babar par le bas pour √©ventuellement le lier
     */
    void update_pos();

    /**
     * 	@brief Mise √  jour de la vitesse
     */
    virtual void update_speed();

    /**
     * 	@brief lie Babar √  la plateforme
     */
    virtual void bind();

    /**
     * 	@brief delie Babar de la plateforme
     */
    void unbind();


    /**
     * 	@brief Accesseur
     *	@return La vitesse actuelle de la plateforme
     */
    Rect speed() const;

    bool is_going_down();


    /**
     * 	@brief Indique si Babar doit etre li√© √  la plateforme
     *	@return Vrai si Babar doit etre li√© √  la plateforme courante
     */
    bool check_babar();

    /**
     *	@brief Indique si la plateforme doit etre supprimee
     *	@return Vrai si oui
     */
    bool dead();

    /**
     * 	@brief Indique si la plateforme est en √©tat d'etre liee
     *	@return Vrai si la plateforme peut etre liee
     */
    bool can_bind();

#ifdef DEBUG_COLL
    void display_coll (Camera *camera);
#endif

};







#endif
