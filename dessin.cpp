#include "dessin.h"
#include <SDL/SDL.h>


void setpixel(SDL_Surface *surface,int x,int y,Uint32 pixel)
{
	if(x>=0 && x<surface->w && y>=0 && y<surface->h)
	{
		int bpp = surface->format->BytesPerPixel;
	
		Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	
		switch(bpp) {
		case 1:
			*p = pixel;
			break;
	
		case 2:
			*(Uint16 *)p = pixel;
			break;
	
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			} else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;
	
		case 4:
			*(Uint32 *)p = pixel;
			break;
		}
    }
}

Uint32 getpixel(SDL_Surface *surface,int x,int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;
    }
}

void getpixelcolor(SDL_Surface * surface,int x,int y,Uint8 *r,Uint8 *g,Uint8 *b)
{
    SDL_GetRGB(getpixel(surface,x,y),surface->format,r,g,b);
}

void ligne_horizontale(SDL_Surface *surface,int x,int y,int longueur,Uint32 couleur)
{
	SDL_LockSurface(surface);
	int i=x;
	while(i<x+longueur)
	{
		setpixel(surface,i,y,couleur);
		i++;
	}
	SDL_UnlockSurface(surface);
}

void disque(SDL_Surface *surface,int x,int y,int rayon,Uint32 couleur)
{
	int cerclex=0,cercley=rayon,d=(5-rayon)/4;
	ligne_horizontale(surface,x-rayon,y,rayon*2,couleur);
	while(cercley>cerclex)
	{
		if(d<0)
		{
			d+=cerclex*2+3;
		}
		else
		{
			d+=cerclex*2-cercley*2+5;
			cercley--;
		}
		cerclex++;
		ligne_horizontale(surface,x-cerclex,y+cercley,cerclex*2,couleur);
		ligne_horizontale(surface,x-cerclex,y-cercley,cerclex*2,couleur);
		ligne_horizontale(surface,x-cercley,y+cerclex,cercley*2,couleur);
		ligne_horizontale(surface,x-cercley,y-cerclex,cercley*2,couleur);
	}
}

void image(SDL_Surface *surface,SDL_Surface *surface_image,int x,int y,int largeur,Uint32 transparence)
{
	if(x+largeur>=0 && x<1024 && y+largeur*surface_image->h/surface_image->w>=0 && y<768)
	{
		int nouveaux,nouveauy/*,couleur,nombre_pixels_regoupes,moyenne_couleur_rouge,moyenne_couleur_verte,moyenne_couleur_bleue,i*/,ancienx=-1,ancieny=-1;
		double zoom=(double)largeur/(surface_image->w);
		Uint8 rouge=123,vert=123,bleu=123;
		SDL_LockSurface(surface);
		for(nouveaux=0;nouveaux<(int)(surface_image->w*zoom);nouveaux++)
		{
			for(nouveauy=0;nouveauy<(int)(surface_image->h*zoom);nouveauy++)
			{
				if((zoom<=1 || !(ancienx==(int)(nouveaux/zoom) && ancieny==(int)(nouveauy/zoom))) && (int)(nouveaux/zoom)<surface_image->w && (int)(nouveaux/zoom)>=0 && (int)(nouveauy/zoom)<surface_image->h && (int)(nouveauy/zoom)>=0) getpixelcolor(surface_image,(int)(nouveaux/zoom),(int)(nouveauy/zoom),&rouge,&vert,&bleu);
				if(transparence!=SDL_MapRGB(surface->format,rouge,vert,bleu)) setpixel(surface,nouveaux+x,nouveauy+y,SDL_MapRGB(surface->format,rouge,vert,bleu));
				if(zoom>1 && ancienx!=(int)(nouveaux/zoom) && ancieny!=(int)(nouveauy/zoom))
				{
					ancienx=(int)(nouveaux/zoom);
					ancieny=(int)(nouveauy/zoom);
				}
			}
		}
		SDL_UnlockSurface(surface);
	}
}


void Image::chargement(SDL_Surface *image)
{
	this->image_originale=image;
}

SDL_Surface* Image::afficher(double largeur)
{
	double zoom=largeur/this->image_originale->w;
	if(zoom>1)
	{
		zoom=2;
	}
	else
	{
		zoom=0.5;
	}
	if(zoom==1) return this->image_originale;
	else largeur=this->image_originale->w*zoom;
	for(int i=0;i<10;i++)
	{
		if(largeur==this->taille_images[i]) return this->images[i];
	}
	if(this->imagei<10)
	{
		images[this->imagei]=(SDL_Surface*)malloc(sizeof(SDL_Surface));
		image(this->images[this->imagei],this->image_originale,0,0,(int)largeur,SDL_MapRGB(this->image_originale->format,255,255,255));
		this->taille_images[this->imagei]=largeur;
		this->imagei++;
		return this->images[this->imagei];
	}
	else
	{
		return this->image_originale;
	}
}
