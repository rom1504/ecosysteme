#include <SDL/SDL.h>

void setpixel(SDL_Surface *surface,int x,int y,Uint32 pixel);
Uint32 getpixel(SDL_Surface *surface,int x,int y);
void getpixelcolor(SDL_Surface * surface,int x,int y,Uint8 *r,Uint8 *g,Uint8 *b);
void ligne_horizontale(SDL_Surface *surface,int x,int y,int longueur,Uint32 couleur);
void disque(SDL_Surface *surf, int cx, int cy, int rayon, Uint32 color);
void image(SDL_Surface *surface,SDL_Surface *surface_image,int x,int y,int largeur,Uint32 transparence);

class Image
{
	
	protected:
		SDL_Surface *images[10],*image_originale;
		double taille_images[10];
		int imagei;
	public:
		void chargement(SDL_Surface *image);
		SDL_Surface* afficher(double largeur);
};
