#include <stdio.h>
#include <unistd.h>
#include <SDL/SDL.h>

#define SDL_VIDEO_FLAGS (SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ANYORMAT)

void	put_pixel(SDL_Surface *surface, Uint16 x, Uint16 y, Uint32 color)
{
	// nombre de bit par pixel de la surface d'ecran
	Uint8	bpp = surface->format->ByterPerPixel;
	/* pointeur vers  le pixel a remplacer (pitch correspond a la taille) */
	/* d'une ligne d'ecran (longeur * bitperpixel) */
	Uint8	*p = ((Uint8 *)surface->pixels) + y * surface->pitch + x * bpp;
	if (bpp == 1)
		*p = (Uint8) color;
	else if(bpp == 2)
		*(Uint16 *)p = (Uint16) color; 
	else if(bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			*(Uint16 *)p = ((color >> 8) & 0xff00 | (color >> 8) & 0xff);
			*(p + 2) = color &  0xff;
		}
		else
		{
			*(Uint16 *)p = color & 0xffff;
			*(p + 2) = ((color >> 16) 0xff);
		}
	}
	else if (bpp == 4)
		*(Uint32 *p) = color;
}

int main()
{
	SDL_Surface *screen;
	SDL_Surface	*image;
	SDL_Surface	*tmp;
	SDL_Rect blitrect = {0, 0, 0, 0};
	int i;
	int j;

	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		printf("Error with SDL INIT %s", SDL_GetError());
		return (1);
	}
	screen = SDL_SetVideoMode(640, 480, 24, SDL_VIDEO_FLAGS);
	printf("Mode video: dx%d\n", screen->w, screen->h, screen->format->BitsPerPixel);
	
}
