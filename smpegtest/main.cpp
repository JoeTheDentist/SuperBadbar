#include <SDL/SDL.h>
#include <smpeg/smpeg.h>

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL;
    SMPEG_Info mpg_info;
    SMPEGstatus mpg_status;
    SMPEG *mpg = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    mpg = SMPEG_new("test.mpg", &mpg_info, 1);

    ecran = SDL_SetVideoMode(mpg_info.width, mpg_info.height, 32, SDL_HWSURFACE);
    if (ecran == NULL)
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\nq", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("Exemple d'utilisation de Smpeg", NULL);

    SMPEG_setdisplay(mpg, ecran, NULL, NULL);
    SMPEG_play(mpg);

    mpg_status = SMPEG_status(mpg);

    while(mpg_status == SMPEG_PLAYING)
    {
        mpg_status = SMPEG_status(mpg);
        SDL_Delay(1000);
    }

    SMPEG_stop(mpg);
    SMPEG_delete(mpg);
    mpg = NULL;

    SDL_Quit();

    return EXIT_SUCCESS;
}
