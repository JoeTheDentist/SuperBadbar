#include <iostream>
#include <SDL/SDL.h>
#include <smpeg/smpeg.h>

class VideoMpeg
{
public:
    VideoMpeg();

    bool charge(std::string nom);
    void lecture();
    void libere();
    bool estFinit();

private:
	SDL_Surface *m_screen;
    SMPEG *m_video;
    SMPEG_Info m_info;
    SDL_Surface *m_surface;
    unsigned int m_hauteur;
    SDL_Rect m_position;
};
