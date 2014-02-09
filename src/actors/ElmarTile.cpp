
#include "ElmarTile.h"

#include "sprites/SpritesManager.h"

ElmarTile::ElmarTile (Rect pos, Direction h, unsigned int speedx, unsigned int speedy, unsigned int damage, dmg_chan type)
{
    PRINT_CONSTR (2, "Construction de ElmarTile");
    m_pos = pos;
    m_dir = h;
    m_damage = damage;
    m_life_span = ELMAR_LIFE_SPAN;
    std::string rep = PIC_PROJ_R;

    m_sprite = gGraphics->get_sprites_manager()->add_table (rep + "elmar/elmar", MIDDLEGROUND);
    m_sprite->change_anim (NONE, m_dir);
    m_sprite->rand_pic();
    m_sprite->set_pos (m_pos);
    m_pos.h = m_sprite->h();
    m_pos.w = m_sprite->w();

    m_speed.x = speedx;
    m_speed.y = speedy;

    m_dead = false;
    m_phase = 0;

    m_invincible = false;

    m_chan = type;
}

ElmarTile::~ElmarTile()
{
    PRINT_CONSTR (2, "Destruction de ElmarTile");
}

void ElmarTile::update_pos (CollisionsManager *CollisionsManager)
{
    m_sprite->set_pos (m_pos);
    m_pos.h = m_sprite->h();
    m_pos.w = m_sprite->w();
    m_phase++;
    unsigned int coll;
    /* cas où le sprite descend */
    for (int speed_y = m_speed.y ; speed_y > 0 ; speed_y -= BOX_SIZE)
    {
        coll = CollisionsManager->get_matrix()->down_collision_type (m_pos);
        if (CollisionsManager::is_down_coll (coll) )
        {
            m_dead = true;
        }
        else
        {
            m_pos.y += BOX_SIZE;
        }
    }

    /* cas où le sprite monte */
    for (int speed_y = m_speed.y ; speed_y < 0 ; speed_y += BOX_SIZE)
    {
        if (CollisionsManager::is_up_coll (CollisionsManager->get_matrix()->up_collision_type (m_pos) ) )
        {
            m_dead = true;
        }
        else
        {
            m_pos.y -= BOX_SIZE;
        }
    }

    /* cas où le sprite va a droite */
    for (int speed_x = m_speed.x ; speed_x > 0 ; speed_x -= BOX_SIZE)
    {
        if (CollisionsManager::is_down_coll (CollisionsManager->get_matrix()->down_collision_type (m_pos) ) )
            m_dead = true;
        m_pos.x += BOX_SIZE;
    }

    /* cas où le sprite va a gauche */
    for (int speed_x = m_speed.x ; speed_x < 0 ; speed_x += BOX_SIZE)
    {
        if (CollisionsManager::is_down_coll (CollisionsManager->get_matrix()->down_collision_type (m_pos) ) )
        {
            m_dead = true;
        }
        m_pos.x -= BOX_SIZE;
    }
    if (m_phase >= m_life_span)
        m_dead = true;
}

void ElmarTile::update_speed()
{

}

void ElmarTile::update_state()
{
    if ( m_speed.x > 0 )
    {
        m_dir = LEFT;
    }
    else
    {
        m_dir = RIGHT;
    }
    m_sprite->change_anim (NONE, m_dir);
    m_sprite->rand_pic();
}

void ElmarTile::set_chan (dmg_chan chan)
{
    m_chan = chan;
}

unsigned int ElmarTile::damage() const
{
    return m_damage;
}

Rect ElmarTile::speed() const
{
    return m_speed;
}

bool ElmarTile::dead() const
{
    return m_dead;
}

void ElmarTile::kill()
{
    m_dead = true;
    if ( !m_invincible )
    {
        m_sprite->set_to_delete();
    }
    m_sprite = NULL;
}

bool ElmarTile::invincible()
{
    return m_invincible;
}
