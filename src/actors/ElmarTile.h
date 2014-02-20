#ifndef ElmarTile_H
#define ElmarTile_H

#include "actors/Projectile.h"

class ElmarTile : public Projectile
{
public:
    /**
     *  @brief Constructeur
     */
    ElmarTile (Rect pos, Direction h, unsigned int speedx, unsigned int speedy, unsigned int damage, dmg_chan type = ALL);

    /**
     * 	@brief Destructeur
     */
    ~ElmarTile();

    /**
     * 	@brief Met a jour la position du ElmarTile
     *	@param CollisionsManager Gestionnaire de collisions
     */
    virtual void update_pos (CollisionsManager *CollisionsManager);

    /**
     * 	@brief Met a jour de la direction du ElmarTile
     */
    virtual void update_state();

    /**
     * 	@brief Met a jour la position du ElmarTile
     */
    virtual void update_speed();

    /**
     * 	@brief Mutateur
     */
    void set_chan (dmg_chan chan);

    /**
     * 	@brief Accesseur
     *	@return Le nombre de points de vies que fait perdre le ElmarTile
     */
    virtual unsigned int damage() const;

    /**
     * 	@brief Accesseur
     *	@return La vitesse du ElmarTile
     */
    virtual Rect speed() const;   /* Accesseur */

    /**
     *	@brief Accesseur
     *	@return Vrai si le Projectile doit etre supprime
     */
    virtual bool dead() const;

    /**
     *	@brief Mutateur: "tue" le ElmarTile
     */
    virtual void kill();

    /**
     *  @brief Acceseur
     */
    bool invincible();
};

#endif // ElmarTile_H
