/***********************************************
 ******************** FONT *********************
 ***********************************************
 ***** Fonction simple d'�criture avec SDL *****
 ***********************************************
 ******* Par R�mi RAMPIN, alias remram44 *******
 ************** www.remram44.c.la **************
 *********** remi.rampin@laposte.net ***********
 ***********************************************/

/*

Ce header est un genre de librairie. Elle sert � afficher du texte avec SDL
(www.libsdl.org)

Cr�ateur original : remram44 (R�mi RAMPIN)
www.remram44.c.la    remi.rampin@laposte.net

Version 1.1   Nouveaut� :
    - couleurs

*/

#ifndef FONT_INCLUDED
#define FONT_INCLUDED

#include <SDL/SDL.h>

class Font {

private:
    SDL_Surface* surface;
    int width,height,r,g,b;

public:
    Font();
    int SetFont(const char * file,int w,int h,int r=0,int g=0,int b=0);
    ~Font();
    void Char(int x,int y,SDL_Surface * surf,int color,char carac);
    void Text(int x,int y,SDL_Surface * surf,bool colored,
        const char * texte,...);
};

#endif

/*

// Exemple d'utilisation :

#include <SDL/SDL.h> // SDL

#include "font.h"    // Ce header

int main(int argc,char **argv)
{
    // Initialisation de SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* sScreen = SDL_SetVideoMode(1024,768,32,
                           SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
    SDL_ShowCursor(0);

    // Cr�ation d'une fonte
    Font fonte;

    // On charge une fonte
    fonte.SetFont("carac.bmp",8,16);

    // On �crit simplement du texte � l'�cran
    // true indique que les couleurs sont activ�es
    fonte.Text(20,100,sScreen,true,"^4Voyez ^1www.remram44.fr.st^4 pour plus "
        "d'informations et pour les derni�res versions.");
    fonte.Text(20,116,sScreen,"^9ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrst"
        "uvwxyz0123456789+-*!/:;,?.������*");

    // On �crit un nombre
    fonte.Text(200,232,sScreen,"^2%d",2005);

    // On affiche
    SDL_Flip(sScreen);

    // On attend 5 secondes
    SDL_Delay(5000);

    // Puis on quitte SDL
    SDL_FreeSurface(sScreen);
    SDL_ShowCursor(1);
    SDL_Quit();

    return 0;
}

*/
