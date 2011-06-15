#ifndef ELMAR_TILE_H
#define ELMAR_TILE_H

#include "projectiles.h"

class Elmar_tile : public Projectile
{
    public:
        /**
         *  @brief Constructeur
         */
        Elmar_tile(Rect pos, direction h, unsigned int speedx, unsigned int speedy, unsigned int damage, dmg_chan type = ALL);

        /*!
         * 	@brief Destructeur
        */
         ~Elmar_tile();

        /*!
         * 	@brief Met à jour la position du Elmar_tile
         *	@param collisions_manager Gestionnaire de collisions
        */
        virtual void update_pos(Collisions_manager *collisions_manager);

        /*!
         * 	@brief Met à jour de la direction du Elmar_tile
        */
        virtual void update_state();

        /*!
         * 	@brief Met à jour la position du Elmar_tile
        */
        virtual void update_speed();

        /*!
         * 	@brief Mutateur
        */
        void set_chan(dmg_chan chan);

        /*!
         * 	@brief Accesseur
         *	@return Le nombre de points de vies que fait perdre le Elmar_tile
        */
        virtual unsigned int damage() const;

        /*!
         * 	@brief Accesseur
         *	@return La vitesse du Elmar_tile
        */
        virtual Rect speed() const;   /* Accesseur */

        /*!
         *	@brief Accesseur
         *	@return Vrai si le Projectile doit etre supprimé
        */
        virtual bool dead() const;

        /*!
         *	@brief Mutateur: "tue" le Elmar_tile
        */
        virtual void kill();

        /**
         *  @brief Acceseur
         */
        bool invincible();
};

#endif // ELMAR_TILE_H
