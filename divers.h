#include "construction.h"
#include "etrevivant.h"
#include <SDL/SDL.h>

double timer();
double abs(double nombre);
int chose_plus_proche(int numero,int type,Etrevivant *etrevivant,int espece,int but);
bool comparaison(double variable1,double variable2,bool type_comparaison);
bool collision(double x1,double x2,double y1,double y2,double w1,double w2,double h1,double h2,bool type_comparaison);
bool collision(double x1,double x2,double y1,double y2,double w1,double w2,double h1,double h2,bool type_comparaison,double marge);
int arbre_hasard(int numero,Etrevivant *etrevivant,int type);
void sauvegarder(Etrevivant *etrevivant);
void charger(char*emplacement,Etrevivant *etrevivant);
bool bouton(double x,double y,double w,double h,bool clic,double xclic,double yclic);
bool bouton(double x,double y,double w,double h,bool clic,double xclic,double yclic,SDL_Surface * sEcran,Uint32 couleur);
double puissance(double nombre,int nombre_puissance);
double conversion_chaine(char truc_en_cours[64]);
int conversion_chaine(char truc_en_cours[64],bool rien);
