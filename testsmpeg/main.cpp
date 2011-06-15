#include "videompeg.h"

int main()
{

	VideoMpeg intro;

	// dans l'initialisation, on charge notre video
	intro.charge("ma_video.mpg");

	// Dans la boucle, on la lit et on sort de la boucle quand elle est finit
	intro.lecture();
	while (!intro.estFinit())
	{
		intro.lecture();
	}

	// On libère quand on as quitter la boucle
	intro.libere();
}
