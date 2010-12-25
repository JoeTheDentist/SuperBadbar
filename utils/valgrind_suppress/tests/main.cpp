
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <fmod/fmod.h>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	FSOUND_Init(44100, 32, 0);
    srand(time(NULL));
	
	SDL_Surface *m_screen = SDL_SetVideoMode(500, 500, 32, SDL_HWSURFACE | SDL_DOUBLEBUF /*| SDL_FULLSCREEN*/);	
	SDL_Event event;
	SDL_Surface *surface = SDL_LoadBMP("../../../pic/boom.bmp");
	SDL_Rect pos;
	pos.x = -4;
	pos.y = -4;
	pos.h =surface->h;
	SDL_BlitSurface(surface, NULL, m_screen, &pos);
	SDL_Flip(m_screen);
	std::string font_name =  "../../../data/talks/fonts/font1.ttf";
	SDL_Color m_font_color;
	m_font_color.r = 255;
	m_font_color.g = 255;
	m_font_color.b = 255;
	TTF_Font *m_font = TTF_OpenFont(font_name.c_str(), 30);
	SDL_Surface *munitions_pictures = TTF_RenderText_Blended(m_font, "ojh", m_font_color);

	bool quitter = false;
	while(!quitter)
	while(SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT :
				quitter = true;
				break;
		}
	}	
	SDL_FreeSurface(surface);
	SDL_FreeSurface(munitions_pictures);
	TTF_CloseFont(m_font);
	int yopeorh = SDL_GetTicks();
	
	
	
	SDL_FreeSurface(m_screen);
	

	FSOUND_Close();
	TTF_Quit();
	SDL_Quit();
	
	std::ifstream input("Makefile", std::ios::in);
	if (!input) {
		std::cout << "FICHIER INTROUVABLE" << std::endl;
		return 0;
	}	
	std::string yop;
	input >> yop;
	input.close();

}
