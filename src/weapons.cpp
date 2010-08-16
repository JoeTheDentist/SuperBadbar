#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>

#include "sprites.h"
#include "globals.h"
#include "weapons.h"

Weapon::Weapon()
{
    m_weapon_type = GUN;
    m_reload_time = 10;
}

Weapon::Weapon(weapon_type type)
{
    m_weapon_type = type;

    switch (m_weapon_type) {
        case GUN :
            m_reload_time = 10;
            break;
        case MACHINEGUN:
            m_reload_time = 1;
            break;
        case SHUTGUN:
            m_reload_time = 5;
            break;
    }
}

Weapon::~Weapon()
{

}

void Weapon::fire(SDL_Rect pos, horizontal h, vertical v)
{
    switch (m_weapon_type) {
        case GUN :
            Projectile * proj;
            proj = new Projectile(pos, h, v, (h-1)*PROJ_SPEED, (v-1)*PROJ_SPEED);
            projectiles.add(proj);
            break;
        case MACHINEGUN:
            /*Projectile * proj;*/
            proj = new Projectile(pos, h, v, (h-1)*PROJ_SPEED, (v-1)*PROJ_SPEED);
            projectiles.add(proj);
            break;
        case SHUTGUN:
            /*uint32_t x[5];
            uint32_t y[5];
            Projectile * proj[5];
            if(h&&v) { /* le tir se fait en diagonale *//*

            }
            else if(h) {

            }
            else {

            }
            for(int i = 0;i<5;i++) {
                proj[i] = new Projectile(pos, h, v, (h-1)*x[i], (v-1)*y[i]);
            }*/
            /*Projectile * proj;*/
            proj = new Projectile(pos, h, v, (h-1)*PROJ_SPEED, (v-1)*PROJ_SPEED);
            projectiles.add(proj);
            break;
    }
}

uint32_t Weapon::reload_time()
{
    return m_reload_time;
}
