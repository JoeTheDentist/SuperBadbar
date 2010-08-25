#include <iostream>
#include <SDL/SDL.h>
#include <stdint.h>
#include <time.h>

#include "sprites.h"
#include "globals.h"
#include "weapons.h"

Weapon::Weapon()
{
    m_weapon_type = GUN;
    m_reload_time = 2;
}

Weapon::Weapon(weapon_type type)
{
    m_weapon_type = type;

    switch (m_weapon_type) {
        case GUN :
            m_reload_time = 2;
            break;
        case MACHINEGUN:
            m_reload_time = 1;
            break;
        case SHOTGUN:
            m_reload_time = 10;
            break;
    }
}

Weapon::~Weapon()
{

}

void Weapon::fire(SDL_Rect pos, horizontal h, vertical v)
{
    Projectile * proj;
    switch (m_weapon_type) {
        case GUN :
            proj = new Projectile(pos, h, v, (h-1)*PROJ_SPEED, (v-1)*PROJ_SPEED,1);
            projectiles_firend.add(proj);
            break;
        case MACHINEGUN:
            proj = new Projectile(pos, h, v, (h-1)*PROJ_SPEED, (v-1)*PROJ_SPEED,1);
            projectiles_firend.add(proj);
            break;
        case SHOTGUN:
            int x[5];
            int y[5];

            Projectile * proj[5];
            if((h-1)&&(v-1)) { /* le tir se fait en diagonale */
                x[0] = 3*PROJ_SPEED/4;
                x[1] = 7*PROJ_SPEED/8;
                x[2] = PROJ_SPEED;
                x[3] = PROJ_SPEED;
                x[4] = PROJ_SPEED;

                y[0] = PROJ_SPEED;
                y[1] = PROJ_SPEED;
                y[2] = PROJ_SPEED;
                y[3] = 7*PROJ_SPEED/8;
                y[4] = 3*PROJ_SPEED/4;

                for(int i = 0;i<5;i++) {
                    proj[i] = new Projectile(pos, h, v, (h-1)*x[i] + rand()%3-1, (v-1)*y[i] + rand()%3-1,1);
                    projectiles_firend.add(proj[i]);
                }
            }
            else if(h-1) { /* tir uniquement dans la dimention horizontale */
                for(int i = 0;i<5;i++) {
                    x[i] = PROJ_SPEED;
                }
                y[0] = /*3*PROJ_SPEED/10*/4;
                y[1] = /*3*PROJ_SPEED/20*/2;
                y[2] = 0;
                y[3] = /*-3*PROJ_SPEED/20*/2;
                y[4] = /*-3*PROJ_SPEED/10*/4;

                for(int i = 0;i<5;i++) {
                    proj[i] = new Projectile(pos, h, v, (h-1)*x[i] + rand()%3-1, y[i] + rand()%3-1,1);
                    projectiles_firend.add(proj[i]);
                }
            }
            else {  /* tir uniquement dans la dimension verticale */
                for(int i = 0;i<5;i++) {
                    y[i] = PROJ_SPEED;
                }
                x[0] = PROJ_SPEED/7;
                x[1] = PROJ_SPEED/14;
                x[2] = 0;
                x[3] = -PROJ_SPEED/14;
                x[4] = -PROJ_SPEED/7;

                for(int i = 0;i<5;i++) {
                    proj[i] = new Projectile(pos, h, v, x[i] + rand()%3-1, (v-1)*y[i] + rand()%3-1,1);
                    projectiles_firend.add(proj[i]);
                }
            }
            break;
    }
}

uint32_t Weapon::reload_time()
{
    return m_reload_time;
}
