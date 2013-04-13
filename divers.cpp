#include "divers.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

double timer()
{
    return SDL_GetTicks();
}

double abs(double nombre)
{
	return (nombre>=0) ? nombre : -nombre;
}

bool comparaison(double variable1,double variable2,bool type_comparaison)/* 0 infèrieure, 1 infèrieur ou égal */
{
	return type_comparaison ? variable1>=variable2 : variable1>variable2;
}

bool collision(double x1,double x2,double y1,double y2,double w1,double w2,double h1,double h2,bool type_comparaison)
{
	return comparaison(x2+w2,x1,type_comparaison) &&
					
			comparaison(x1+w1,x2,type_comparaison) &&
					
			comparaison(y2+h2,y1,type_comparaison) &&
					
			comparaison(y1+h1,y2,type_comparaison);
}

bool collision(double x1,double x2,double y1,double y2,double w1,double w2,double h1,double h2,bool type_comparaison,double marge)
{
	double autre_marge=1-marge;
	x1+=x1*autre_marge;
	x2+=x2*autre_marge;
	y1+=y1*autre_marge;
	y2+=y2*autre_marge;
	w1*=marge-autre_marge;
	w2*=marge-autre_marge;
	h1*=marge-autre_marge;
	h2*=marge-autre_marge;
	return collision(x1,x2,y1,y2,w1,w2,h1,h2,type_comparaison);
}

int arbre_hasard(int numero,Etrevivant *etrevivant,int type)
{
	int etrevivanti,i,nombre_genes=12;
	double comparaison_genes;
	for(etrevivanti=0;etrevivanti<5000;etrevivanti++)
	{
		if(etrevivant[etrevivanti].savoirvie() && numero!=etrevivanti && etrevivant[etrevivanti].savoirreproduction_voulue() && etrevivant[etrevivanti].savoirtype()==type)
		{
			comparaison_genes=0;
			for(i=1;i<13;i++)
			{
				if(etrevivant[numero].savoirgene(i)!=0 && etrevivant[etrevivanti].savoirgene(i)!=0)
				{
					comparaison_genes+=(etrevivant[numero].savoirgene(i)>=etrevivant[etrevivanti].savoirgene(i) ? (etrevivant[numero].savoirgene(i)/etrevivant[etrevivanti].savoirgene(i)) : (etrevivant[etrevivanti].savoirgene(i)/etrevivant[numero].savoirgene(i)));
				}
				else
				{
					nombre_genes--;
				}
			}
			comparaison_genes/=nombre_genes;
			if(comparaison_genes<=1+etrevivant[numero].savoirgene(11)) return etrevivanti;
		}
	}
	return 0;// ?
}

int chose_plus_proche(int numero,int type,Etrevivant *etrevivant,int espece,int but)
{
	int chose_plus_proche=numero,etrevivanti,i,nombre_genes=12;
	double comparaison_genes;
	for(etrevivanti=0;etrevivanti<5000;etrevivanti++)
	{
		if(etrevivant[etrevivanti].savoirvie() && numero!=etrevivanti && etrevivant[etrevivanti].savoirtype()==type && ((etrevivant[etrevivanti].savoirtype()==1 && but!=1 && etrevivant[etrevivanti].savoirfruit()>5) || etrevivant[etrevivanti].savoirtype()!=1 || but==1) && (but!=1 || etrevivant[etrevivanti].savoirreproduction_voulue()))
		{
			if(sqrt(abs(etrevivant[chose_plus_proche].savoirx()-etrevivant[numero].savoirx())*abs(etrevivant[chose_plus_proche].savoirx()-etrevivant[numero].savoirx())+abs(etrevivant[chose_plus_proche].savoiry()-etrevivant[numero].savoiry())*abs(etrevivant[chose_plus_proche].savoiry()-etrevivant[numero].savoiry()))>sqrt(abs(etrevivant[etrevivanti].savoirx()-etrevivant[numero].savoirx())*abs(etrevivant[etrevivanti].savoirx()-etrevivant[numero].savoirx())+abs(etrevivant[etrevivanti].savoiry()-etrevivant[numero].savoiry())*abs(etrevivant[etrevivanti].savoiry()-etrevivant[numero].savoiry())) || chose_plus_proche==numero)
			{
				comparaison_genes=0;
				for(i=1;i<13;i++)
				{
					if(etrevivant[numero].savoirgene(i)!=0 && etrevivant[etrevivanti].savoirgene(i)!=0)
					{
						comparaison_genes+=(etrevivant[numero].savoirgene(i)>=etrevivant[etrevivanti].savoirgene(i) ? (etrevivant[numero].savoirgene(i)/etrevivant[etrevivanti].savoirgene(i)) : (etrevivant[etrevivanti].savoirgene(i)/etrevivant[numero].savoirgene(i)));
					}
					else
					{
						nombre_genes--;
					}
				}
				comparaison_genes/=nombre_genes;
				if(espece==0 || (espece==1 && comparaison_genes>1+etrevivant[numero].savoirgene(11)) || (espece==2 && comparaison_genes<=1+etrevivant[numero].savoirgene(11))) chose_plus_proche=etrevivanti;
			}
		}
	}

	return chose_plus_proche;
}

bool bouton(double x,double y,double w,double h,bool clic,double xclic,double yclic)
{
	return collision(x,xclic,y,yclic,w,1,h,1,1) && clic;
}

bool bouton(double x,double y,double w,double h,bool clic,double xclic,double yclic,SDL_Surface * sEcran,Uint32 couleur)
{
	SDL_Rect affichage;
	affichage.x=(int)x;
	affichage.y=(int)y;
	affichage.w=(int)w;
	affichage.h=(int)h;
	SDL_FillRect(sEcran,&affichage,couleur);
	return bouton(x,y,w,h,clic,xclic,yclic);		
}

void sauvegarder(Etrevivant *etrevivant)
{
    ofstream fichier;
    int etrevivanti,i;
    fichier.open("save.adn",ios::out|ios::trunc|ios::binary);
	for(etrevivanti=0;etrevivanti<5000;etrevivanti++)
	{
		if(etrevivant[etrevivanti].savoirvie())
		{
			fichier<<etrevivant[etrevivanti].savoirx();
			fichier<<" "<<etrevivant[etrevivanti].savoiry();
			fichier<<" "<<etrevivant[etrevivanti].savoirventre();
			fichier<<" "<<etrevivant[etrevivanti].savoirsoif();
			fichier<<" "<<etrevivant[etrevivanti].savoirtype();
			fichier<<" "<<etrevivant[etrevivanti].savoircroissance();
			fichier<<" "<<etrevivant[etrevivanti].savoirfruit();
			for(i=1;i<13;i++)
			{
				fichier<<" "<<etrevivant[etrevivanti].savoirgene(i);
			}
			fichier<<" _\n";
		
		}
	}
	fichier.close();
}

double puissance(double nombre,int nombre_puissance)
{
	int i;
	double nombre_retour=nombre;
	for(i=0;i<nombre_puissance+1;i++) nombre_retour/=nombre;
	return nombre_retour;
}

double conversion_chaine(char truc_en_cours[64])
{
	int i,point=-1,chiffre,signe=1;
	double nombre=0.0;
	for(i=0;i<64;i++)
	{
		chiffre=-1;
		switch(truc_en_cours[i])
		{
			case '-':
				signe=-1;
			break;
			
			case '0':
				chiffre=0;
			break;
			
			case '1':
				chiffre=1;
			break;
			
			case '2':
				chiffre=2;
			break;
			
			case '3':
				chiffre=3;
			break;
			
			case '4':
				chiffre=4;
			break;
			
			case '5':
				chiffre=5;
			break;
			
			case '6':
				chiffre=6;
			break;
			
			case '7':
				chiffre=7;
			break;
			
			case '8':
				chiffre=8;
			break;
			
			case '9':
				chiffre=9;
			break;
			
			case '.':
				point=i;
			break;
		}
		if(chiffre!=-1) nombre=point==-1 ? nombre*10.0+chiffre : nombre+chiffre*puissance(10,i-point);
	}
	return nombre*signe;
}
int conversion_chaine(char truc_en_cours[64],bool rien)
{
	return (int)conversion_chaine(truc_en_cours);
}

void charger(char*emplacement,Etrevivant *etrevivant)
{
    ifstream fichier;
    int a,i=0,longueur_en_cours=0,nb=0,type,etrevivanti;
    fichier.open(emplacement,ios::in|ios::binary);
    char octet,truc_en_cours[64];
	double x,y,ventre,croissance,soif,genes[13],nombre_converti,fruit;
	for(etrevivanti=0;etrevivanti<5000;etrevivanti++) etrevivant[etrevivanti].mort();
	for(a=0;a<64;a++) truc_en_cours[a]=0;
    while(true)
    {
		if(!fichier.read(&octet,1)) break;

		if(octet==' ')
		{	
			nombre_converti=conversion_chaine(truc_en_cours);
			switch(i)
			{
				case 0:
					x=nombre_converti;
				break;
				
				case 1:
					y=nombre_converti;
				break;
				
				case 2:
					ventre=nombre_converti;
				break;
				
				case 3:
					soif=nombre_converti;
				break;
				
				case 4:
					type=conversion_chaine(truc_en_cours,1);
				break;
				
				case 5:
					croissance=nombre_converti;
				break;
				
				case 6:
					fruit=nombre_converti;
				break;
				
				default:
					genes[i-6]=nombre_converti;
				break;
			}
			
			i++;
			longueur_en_cours=0;
			for(a=0;a<64;a++) truc_en_cours[a]='a';
		}
		else if(octet=='_')
		{
			etrevivant[nb].creation(genes[1],genes[2],genes[3],genes[4],genes[5],genes[6],genes[7],genes[8],genes[9],genes[10],genes[11],genes[12],x,y,ventre,type,croissance,soif,fruit,100);
			longueur_en_cours=0;
			i=0;
			nb++;
		}
		else
		{
			truc_en_cours[longueur_en_cours]=octet;
			longueur_en_cours++;
		}
	}
	fichier.close();
}
