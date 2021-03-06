#ifndef SPRITES_ANIM_TABLE_H_INCLUDED
#define SPRITES_ANIM_TABLE_H_INCLUDED

#include "Sprite.h"
#include "video/AnimTable.h"

class SpriteAnimTable : public Sprite
{
private:
    AnimTable * m_animt;   /* gestionnaire d'animations */

public:
    /**
     * Constructeur
     */
    SpriteAnimTable (std::string anim_name, screen_level lvl);

    /**
     * Destructeur
     */
    virtual ~SpriteAnimTable();

    /**
     * Image a afficher
     *  +maj de m_pos
     */
    Surface * curr_pic();

    /**
     * Passe a l'image suivante
     */
    void next_pic();

    /**
     *	@brief Change l'etat
     */
    void change_anim (int s, Direction dir, bool fire = false , bool phase_rand = false);

    /**
     *  @brief Hauteur
     *  @return Hauteur
     */
    int h();

    /**
     *  @brief Largeur
     *  @return Largeur
     */
    int w();

    /**
     *	Set to a random picture
     */
    void rand_pic();
};

#endif // SPRITES_ANIM_TABLE_H_INCLUDED
