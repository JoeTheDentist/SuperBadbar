
#include "videompeg.h"

using namespace std;

//-----------------------------------------------------------------------
VideoMpeg::VideoMpeg() : m_video(NULL), m_surface(NULL), m_hauteur(0)
{
	m_screen = SDL_SetVideoMode(800, 600, 32, SDL_HWPALETTE | SDL_DOUBLEBUF /*| SDL_FULLSCREEN*/);
}

//-----------------------------------------------------------------------
bool VideoMpeg::charge(string nom)
{
	m_video = SMPEG_new(nom.c_str(), &m_info, 1);
    if (SMPEG_error(m_video))
    {
                cerr << "Impossible de charge la video " << nom << endl;
        return false;
    }

    m_hauteur = (SDL_GetVideoSurface()->w/m_info.width)*m_info.height;
    m_surface = SDL_AllocSurface(SDL_HWSURFACE, SDL_GetVideoSurface()->w, m_hauteur, 24, 0, 0, 0, 0);
    if (m_surface == NULL)
    {
                cerr << "Impossible d'allouer la surface vidéo du fichier " << nom << endl;
        return false;
    }

    SMPEG_setdisplay(m_video, m_screen, NULL, NULL);
    SMPEG_play(m_video);

    return true;
}

//-----------------------------------------------------------------------
void VideoMpeg::lecture()
{
    if (m_surface)
    {
        m_position.x = 0;
        m_position.y = (SDL_GetVideoSurface()->h/2) - (m_hauteur/2);
        SDL_BlitSurface(m_surface, NULL, SDL_GetVideoSurface(), &m_position);
    }
}

//-----------------------------------------------------------------------
void VideoMpeg::libere()
{
    if (m_surface)
    {
        SDL_FreeSurface(m_surface);
        m_surface = NULL;

        SMPEG_stop(m_video);
        SMPEG_delete(m_video);
        m_video = NULL;
    }
}

//-----------------------------------------------------------------------
bool VideoMpeg::estFinit()
{
    if (SMPEG_status(m_video) != SMPEG_PLAYING)
        return true;
    else
        return false;
}
