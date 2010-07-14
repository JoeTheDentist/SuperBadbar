


#ifndef ANIMATIONS_H_INCLUDED
#define ANIMATIONS_H_INCLUDED

class Animation {
    private:
        uint8_t m_nb_pics;          /* Nombre d'images de l'animation */
        uint8_t m_curr_pic;         /* Numéro image pourr current_pic */
        SDL_Surface ** m_pics;      /* Tableau des images de l'animation */

    public:
        Animation();                /* Constructeur */
        Animation(uint8_t nb_pics, SDL_Surface **pics); /* Constructeur */
        ~Animation();               /* Destructeur */
        uint8_t nb_pics();          /* Accesseur */
        SDL_Surface* current_pic(); /* Retourne l'image à afficher de l'animation */
        void next_pic();            /* Passe à l'image suivante (pour current_pic) */
};

#endif // ANIMATIONS_H_INCLUDED
