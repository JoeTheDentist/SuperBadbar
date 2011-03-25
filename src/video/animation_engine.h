/**
 * 	@file animation_engine.h
 * 	@brief Conteneur et joueur d'animation ind�pendantes
 *
 * 	@author Guillaume B�rard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _ANIMATION_ENGINE_
#define _ANIMATION_ENGINE_

#include <map>

#include "../video/surface.h"
#include "../video/animation.h"
#include "../video/camera.h"


struct anim_pos {
    Rect pos;
    Animation * anim;
    Rect speed;
    bool falling;
};

class Animation_engine {
	private:
        /* listes des noms des animations � jouer */
        std::list<anim_pos> m_anims;
        int m_phase;

	public:

        /**
         *  @brief Constructeur
         */
        Animation_engine();

        /**
         *  @brief Destructeur
         */
        ~Animation_engine();

        /**
         *  @brief Initialisation des animations en fonction d'un analyser (donn� par le niveau: game)
         *  @param lvl : chemin vers dossier lvl courant
         */
        void init(std::string lvl_name);

        /**
         *  @brief Fonction d'ajout
         *  @param pic : nom de l'animation
         *  @param pos : position o� jouer l'animation
         *  @param type : type d'animation
         *  @param falling : si l'animation doit subir la gavit�
         */
        void add(std::string pic, Rect pos, anim_type type, bool falling);

        /**
         *  @brief Fonction d'ajout
         *  @param pic : nom de l'animation
         *  @param pos : position o� jouer l'animation
         *  @param type : type d'animation
         *  @param speed : vitesse de mouvement
         *  @param falling : si l'animation doit subir la gavit�
         */
        void add(std::string pic, Rect pos, anim_type type, Rect speed, bool falling);

        /**
         *  @brief Fonction d'ajout
         *  @param x : absisse
         *  @param y : ordonn�e
         */
        void add(std::string pic, int x, int y);

        /**
         *  @brief Fonction d'ajout
         *  @param x : absisse
         *  @param y : ordonn�e
         *  @param type : type d'animation
         *  @param sx : absisse vitess
         *  @param sy : ordonn�e vitesse
         *  @param falling : si l'animation doit sbir la gravit�
         */
        void add(std::string pic, int x, int y, anim_type type, int sx, int sy, bool falling);

        /**
         *  @brief Affichage des animations
         *  @param camera : camera permettant d'afficher les animations
         */
        void display_anims(Camera * camera);

        /**
         *  @brief Mise � jour des vitesses et positions des animations
         */
        void update();
};

#endif
