/***********************************************
 ******************** FONT *********************
 ***********************************************
 ***** Fonction simple d'écriture avec SDL *****
 ***********************************************
 ******* Par Rémi RAMPIN, alias remram44 *******
 ************** www.remram44.c.la **************
 *********** remi.rampin@laposte.net ***********
 ***********************************************/
 
#include <cstdio>
#include <cstdarg>
#include <SDL/SDL.h>
#include "font.h"

using namespace std;

// Constructeur
Font::Font()
{
    surface=NULL;

    width=0;
    height=0;

    r=0;
    g=0;
    b=0;
}

// Initialisation
int Font::SetFont(const char * file,int w,int h,int r,int g,int b)
{
    if(surface!=NULL)
    {
        SDL_FreeSurface(surface);
        surface=NULL;
    }

    surface=SDL_LoadBMP(file);

    if(surface==NULL)
        return -1;

    // Taille d'un carac
    width=w;
    height=h;

    // Couleur du fond
    this->r=r;
    this->g=g;
    this->b=b;

    return 0;
}

// Quitter
Font::~Font()
{
    if(surface!=NULL)
        SDL_FreeSurface(surface);
}

// Pour écrire un caractère
void Font::Char(int x,int y,SDL_Surface * surf,int color,char carac)
{
    SDL_Rect dest = {(Sint16)x,(Sint16)y,(Uint16)width,(Uint16)height};
    int num=(int)((unsigned char)carac);  // Code ASCII du caractère à afficher
    SDL_Rect src  = {(Sint16)(num*width),(Sint16)(color*height),(Uint16)width,(Uint16)height};

    // Colorkey pour affichage transparent
    SDL_SetColorKey(surface,SDL_SRCCOLORKEY,SDL_MapRGB(surface->format,r,g,b));

    // Blit
    SDL_BlitSurface(surface,&src,surf,&dest);
}

// Pour écrire une chaîne
void Font::Text(int x,int y,SDL_Surface * surf,bool colored,
    const char * texte,...)
{
    // Liste d'arguments
    va_list varg;
    va_start(varg,texte);
    
    // Chaîne à afficher
    char buffer[256];
    vsprintf(buffer,texte,varg);

    // Couleur par défaut : blanc (6)
    int color = 6;

    int dep=x;
    const char* pos=buffer;
    while(*pos!='\0')
    {
        if(*pos=='\n')
        {
            y+=height;
            x=dep;
            pos+=1;
        }
        else if( (*pos=='^') && colored )
        {
            pos+=1;
            if(*pos >='1' && *pos <='9')
            {
                color = *pos-'1';
                pos+=1;
            }
            else
                Char(x,y,surf,color,'^');
        }
        else
        {
            Char(x,y,surf,color,*pos);
            x+=width;
            pos+=1;
        }
    }
}
