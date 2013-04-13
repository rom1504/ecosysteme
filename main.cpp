#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "font.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include "trigonometrie.h"
#include "dessin.h"
#include "divers.h"

using namespace std;
           
int main(int argc,char **argv)
{
	//#include "initialisation.h"
	SDL_Surface * sEcran,*singe,*arbre,*lac;
	singe=SDL_LoadBMP("singe.bmp");
	arbre=SDL_LoadBMP("arbre.bmp");
	lac=SDL_LoadBMP("lac.bmp");
	Image lac_;
	lac_.chargement(lac);
	// initiation de sdl
	SDL_Init(SDL_INIT_VIDEO);
	sEcran = SDL_SetVideoMode(1024, 768, 32,SDL_HWSURFACE|SDL_DOUBLEBUF/*|SDL_FULLSCREEN*/);


	//définition de la variable d'évenement de sdl et du rectangle de l'écran
	SDL_Event event;
	SDL_Rect ecran,affichage;
	ecran.x=0;
	ecran.y=0;
	ecran.w=1024;
	ecran.h=768;


	//declaration des variables
	double temps_clic=timer(),temps=timer(),/*temps_hasard_reproduction=timer(),*/vitesse=timer(),vitesse_speciale,positionx=-2000,positiony=-2000,zoom=0.2/*,deplacementx,deplacementy*/,vitesse_aret,temps_aret=timer(),/*trajectoire_x,trajectoire_y,moyenne,deplacement_actuelx,deplacement_actuely,deplacement_totalx,deplacement_totaly,*/hasard,energie_prise,comparaison_genes,/*vitesse_etrevivant,*/max_etrevivant=500,fruit_mange,acceleration=1,derniere_sauvegarde=timer(),dernier_chargement=timer(),genes_moyens[13];
		
	int unitei,constructioni,xclic=0,yclic=0,i,selectioni_construction=0,selectioni_unite=0,selectioni_arbre=0,selectioni_animaux=0,type_selection,etrevivanti,/*objecti,chose_proche=-1,*/etrevivant_collision,nb=-1,nb_animaux=-1,heure,minute,seconde,etrevivant_selectionne=-1,nombre_genes=12,/*temporaire=0,*/marge=190,x,y,w/*,h*/;
		
	bool clic=0,positionx_augmentation=0,positionx_diminution=0,positiony_augmentation=0,positiony_diminution=0,acceleration_augmentation=0,acceleration_diminution=0,zoom_augmentation=0,zoom_diminution=0,droit=false,ctrl=false,shift=false,carnivore,carnivore_collision,voir_genes_moyens=false;
	srand((int)timer());
	char nom_gene[13][100]={"","Taille maximale","Vitesse maximale","Agressivite","Portee","Energie pour la reproduction","Recherche de reproduction","Plus de recherche de reproduction","Vitesse de croissance","Energie pour croissance","Croissance a la naissance","Compatibilite pour la reproduction","Taille des fruits"};
	Uint32 jaune=SDL_MapRGB(sEcran->format,255,255,0),bleu=SDL_MapRGB(sEcran->format,0,0,255),blanc=SDL_MapRGB(sEcran->format,255,255,255);

		
	//declaration des structures
	Construction construction[1000];
	Type_construction type_construction[1000];
	Unite unite[1000];
	Type_unite type_unite[1000];
	Etrevivant etrevivant[5000];
		
	// Création d'une fonte
	Font ecriture;

	// On charge une fonte
	ecriture.SetFont("carac.bmp",8,16);
		
	//création etres vivants
	for(etrevivanti=0;etrevivanti<5000;etrevivanti++) etrevivant[etrevivanti].mort();
		
	charger((char*)"initialisation.adn",etrevivant);
		
	type_unite[0].creation(10,10,10,10,10,10,100,2000);
	for(unitei=0;unitei<10;unitei++)
	{
		unite[unitei].creation(-500,20*(unitei+1),100,0,type_unite);
	}
		
	type_construction[0].creation(50,50,10,10,10,1000,100000);
	for(constructioni=0;constructioni<1;constructioni++)
	{
		construction[constructioni].creation(-500,300+20*(constructioni+1),1000,0,-400,320,type_construction);
	}

	while(true)
	{	
		vitesse=(timer()-temps)/1000*acceleration;
		vitesse_speciale=(timer()-temps)/1000;
		vitesse_aret=(timer()-temps_aret)*acceleration;
		temps=timer();
		if(positiony_augmentation) positiony+=vitesse_speciale*500/zoom;
		if(positiony_diminution) positiony-=vitesse_speciale*500/zoom;
		if(positionx_augmentation) positionx+=vitesse_speciale*500/zoom;
		if(positionx_diminution) positionx-=vitesse_speciale*500/zoom;
		
		if(zoom_augmentation) { zoom*=1+(vitesse_speciale);}
		if(zoom_diminution) { zoom/=1+(vitesse_speciale);}
		if(acceleration_augmentation) { acceleration*=1+(vitesse_speciale);}
		if(acceleration_diminution) { acceleration/=1+(vitesse_speciale);}
		if(acceleration>10) acceleration=10;
		if(vitesse_speciale>0.100 && max_etrevivant>0) max_etrevivant/=(1+vitesse_speciale/10);
		else
		{
			if(vitesse_speciale<=0.100 && max_etrevivant<5000) max_etrevivant*=(1+vitesse_speciale/10);
		}
		if(max_etrevivant>=5000) max_etrevivant=4999;
		if(max_etrevivant<0) max_etrevivant=0;
		

		//#include "controle.h"
		while(SDL_PollEvent(&event))
		{
			if(event.type==SDL_QUIT)
			{
				SDL_FreeSurface(sEcran);
				SDL_Quit();
				exit(0);
			}
			else if(event.type==SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						SDL_FreeSurface(sEcran);
						SDL_Quit();
						exit(0);
					break;
						
					case SDLK_RIGHT:
						positionx_augmentation=1;
					break;
					
					case SDLK_LEFT:
						positionx_diminution=1;
					break;
					
					case SDLK_DOWN:
						positiony_augmentation=1;
					break;
					
					case SDLK_UP:
						positiony_diminution=1;
					break;
					
					case SDLK_F2:
						zoom_augmentation=1;
					break;
					
					case SDLK_F3:
						zoom_diminution=1;
					break;
						
					case SDLK_F4:
						acceleration_augmentation=1;
					break;
					
					case SDLK_F5:
						acceleration_diminution=1;
					break;
					
					case SDLK_F6:
						if(derniere_sauvegarde+1000<timer())
						{
							derniere_sauvegarde=timer();
							sauvegarder(etrevivant);
						}
					break;
					
					case SDLK_F7:
						if(dernier_chargement+1000<timer())
						{
							dernier_chargement=timer();
							charger((char*)"save.adn",etrevivant);
						}
					break;
						
					case SDLK_F12:
						for(etrevivanti=0;etrevivanti<5000;etrevivanti++)
						{
							if(etrevivant[etrevivanti].savoirvie() && etrevivant[etrevivanti].savoirselection())
							{
								etrevivant[etrevivanti].mort();
							}
						}
					break;
									
					case SDLK_LCTRL:
						ctrl=true;
					break;
						
					case SDLK_LSHIFT:
						shift=true;
					break;
					
					case SDLK_SPACE:
							acceleration=1;
					break;
					
					default:
						
					break;
				}
			}
			else if(event.type==SDL_KEYUP)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_RIGHT:
						positionx_augmentation=0;
					break;
					
					case SDLK_LEFT:
						positionx_diminution=0;
					break;
					
					case SDLK_DOWN:
						positiony_augmentation=0;
					break;
				
					case SDLK_UP:
						positiony_diminution=0;
					break;
					
					case SDLK_F2:
						zoom_augmentation=0;
					break;
					
					case SDLK_F3:
						zoom_diminution=0;
					break;
					
					case SDLK_F4:
						acceleration_augmentation=0;
					break;
					
					case SDLK_F5:
						acceleration_diminution=0;
					break;
					
					case SDLK_LCTRL:
						ctrl=false;
					break;
						
					case SDLK_LSHIFT:
						shift=false;
					break;
					default:
						
					break;
				}
			}
			else if(event.motion.state==3 && event.button.state==1)
			{
				for(unitei=0;unitei<1000;unitei++)
				{
					if(unite[unitei].savoirselection())
					{
						unite[unitei].changerdestinationfinale(event.motion.x/zoom+positionx==0 ? event.motion.x/zoom+positionx+1 : event.motion.x/zoom+positionx,event.motion.y/zoom+positiony==0 ? event.motion.y/zoom+positiony+1 : event.motion.y/zoom+positiony);
					}
				}
				droit=true;
			}
				
			else if(event.motion.state==4 && event.button.state==1)
			{
				zoom*=1.01;
			}
			else if(event.motion.state==5 && event.button.state==1)
			{
				zoom/=1.01;
			}
			else if(event.motion.state==1 && event.button.state==1)
			{
				if(event.motion.y<680 && !ctrl && !shift)
				{
					for(unitei=0;unitei<1000;unitei++)
					{
						if(unite[unitei].savoirvie())
						{
								unite[unitei].deselectionner();
						}
							
					}
					for(constructioni=0;constructioni<1000;constructioni++)
					{
						if(construction[constructioni].savoirvie())
						{
							construction[constructioni].deselectionner();
						}
						
					}
					
					for(etrevivanti=0;etrevivanti<5000;etrevivanti++)
					{
						if(etrevivant[etrevivanti].savoirvie())
						{
							etrevivant[etrevivanti].deselectionner();
						}
					}
					etrevivant_selectionne=-1;
				}
				xclic=event.motion.x;
				yclic=event.motion.y;
				clic=true;
			}
			else if(event.type==SDL_MOUSEBUTTONUP)
			{
				clic=false;
				xclic=0;
				yclic=0;
			}
		}

		
		//#include "traitement_etrevivant.h"
		nb=0;
		nb_animaux=0;
		if(voir_genes_moyens)
		{
			for(i=1;i<13;i++)
			{
				genes_moyens[i]=0;
			}
		}

		for(etrevivanti=0;etrevivanti<5000;etrevivanti++)
		{
			if(etrevivant[etrevivanti].savoirvie())
			{
				if(etrevivant[etrevivanti].savoirtype()==0)
				{
					if(voir_genes_moyens)
					{
						for(i=1;i<13;i++)
						{
							genes_moyens[i]+=etrevivant[etrevivanti].savoirgene(i);
						}
					}
					nb_animaux++;
				}
				nb++;
				if(!etrevivant[etrevivanti].savoircroissance_termine() && etrevivant[etrevivanti].savoircroissance()==100)
				{
					etrevivant[etrevivanti].changercroissance_termine(true);
					etrevivant[etrevivanti].changertaille(etrevivant[etrevivanti].savoirgene(1)*etrevivant[etrevivanti].savoircroissance()/100);
					etrevivant[etrevivanti].changerlargeur(sqrt(etrevivant[etrevivanti].savoirtaille()));
				}
				if(etrevivant[etrevivanti].savoircroissance()<100)
				{
					etrevivant[etrevivanti].changertaille(etrevivant[etrevivanti].savoirgene(1)*etrevivant[etrevivanti].savoircroissance()/100);
					etrevivant[etrevivanti].changerlargeur(sqrt(etrevivant[etrevivanti].savoirtaille()));
				}
				//deplacement
				if(etrevivant[etrevivanti].savoirtype()!=1)
				{
					hasard=myrand();
					if(timer()*acceleration-etrevivant[etrevivanti].savoirderniere_verification()>1000 || !etrevivant[etrevivant[etrevivanti].savoirchose_proche()].savoirvie())
					{
						etrevivant[etrevivanti].changerderniere_verification(timer()*acceleration);
						etrevivant[etrevivanti].changerchose_proche(etrevivant[etrevivanti].savoirveut_boire() ? -2 : (etrevivant[etrevivanti].savoirreproduction_voulue() ? arbre_hasard(etrevivanti,etrevivant,0) : chose_plus_proche(etrevivanti,etrevivant[etrevivanti].savoirgene(3)*hasard>=50 ? 0 : 1,etrevivant,etrevivant[etrevivanti].savoirgene(3)*hasard<50 ? 0 : 1,etrevivant[etrevivanti].savoirreproduction_voulue())));
					}
					if(etrevivant[etrevivanti].savoirchose_proche()!=-1)
					{
						if(etrevivant[etrevivanti].savoirchose_proche()!=-2) etrevivant[etrevivanti].deplacement(etrevivant[etrevivant[etrevivanti].savoirchose_proche()].savoirx(),etrevivant[etrevivant[etrevivanti].savoirchose_proche()].savoiry(),etrevivant[etrevivanti].savoirgene(2)*etrevivant[etrevivanti].savoircroissance()/100*vitesse);
						else etrevivant[etrevivanti].deplacement(100,100,etrevivant[etrevivanti].savoirgene(2)*etrevivant[etrevivanti].savoircroissance()/100*vitesse);
					}
					
				}
				// En cas de collision entre les etres vivants
				
				if(etrevivant[etrevivanti].savoirtype()!=1 && etrevivant[etrevivanti].savoirtemps_collision()+50<timer()*acceleration)
				{
					etrevivant[etrevivanti].changertemps_collision(timer()*acceleration);
					for(etrevivant_collision=0;etrevivant_collision<5000;etrevivant_collision++)
					{
						if(etrevivant[etrevivant_collision].savoirvie() && etrevivant_collision!=etrevivanti)
						{
							if(!etrevivant[etrevivant_collision].savoircroissance_termine() && etrevivant[etrevivant_collision].savoircroissance()==100)
							{
								etrevivant[etrevivant_collision].changercroissance_termine(true);
								etrevivant[etrevivant_collision].changertaille(etrevivant[etrevivant_collision].savoirgene(1)*etrevivant[etrevivant_collision].savoircroissance()/100);
								etrevivant[etrevivant_collision].changerlargeur(sqrt(etrevivant[etrevivant_collision].savoirtaille()));
							}
							if(etrevivant[etrevivant_collision].savoircroissance()<100)
							{
								etrevivant[etrevivant_collision].changertaille(etrevivant[etrevivant_collision].savoirgene(1)*etrevivant[etrevivant_collision].savoircroissance()/100);
								etrevivant[etrevivant_collision].changerlargeur(sqrt(etrevivant[etrevivant_collision].savoirtaille()));
							}
							if(collision(etrevivant[etrevivanti].savoirx(),etrevivant[etrevivant_collision].savoirx(),etrevivant[etrevivanti].savoiry(),etrevivant[etrevivant_collision].savoiry(),etrevivant[etrevivanti].savoirlargeur(),etrevivant[etrevivant_collision].savoirlargeur(),etrevivant[etrevivanti].savoirlargeur(),etrevivant[etrevivant_collision].savoirlargeur(),0))
							{
								etrevivant[etrevivanti].deplacement(etrevivant[etrevivanti].savoirx()+(etrevivant[etrevivanti].savoirx()-etrevivant[etrevivant_collision].savoirx()),etrevivant[etrevivanti].savoiry()+(etrevivant[etrevivanti].savoiry()-etrevivant[etrevivant_collision].savoiry()),etrevivant[etrevivanti].savoirgene(2)*etrevivant[etrevivanti].savoircroissance()/100*vitesse);
							}
						}
					}
				}
			
				if(collision(etrevivant[etrevivanti].savoirx(),-300,etrevivant[etrevivanti].savoiry(),-300,etrevivant[etrevivanti].savoirlargeur(),700,etrevivant[etrevivanti].savoirlargeur(),700,0))
				etrevivant[etrevivanti].deplacement(etrevivant[etrevivanti].savoirx()+(etrevivant[etrevivanti].savoirx()+300),etrevivant[etrevivanti].savoiry()+(etrevivant[etrevivanti].savoiry()+300),etrevivant[etrevivanti].savoirgene(2)*etrevivant[etrevivanti].savoircroissance()/100*vitesse);
				if(collision(etrevivant[etrevivanti].savoirx(),-300,etrevivant[etrevivanti].savoiry(),-300,etrevivant[etrevivanti].savoirlargeur(),700,etrevivant[etrevivanti].savoirlargeur(),700,0,1.1))		
				etrevivant[etrevivanti].changersoif(etrevivant[etrevivanti].savoirsoif()+vitesse*etrevivant[etrevivanti].savoirtaille()/500*etrevivant[etrevivanti].savoirgene(2)*etrevivant[etrevivanti].savoircroissance()/100);
				for(etrevivant_collision=0;etrevivant_collision<5000;etrevivant_collision++)
				{
					if(etrevivant[etrevivant_collision].savoirvie() &&	etrevivant_collision!=etrevivanti)
					{
						if(!etrevivant[etrevivant_collision].savoircroissance_termine() && etrevivant[etrevivant_collision].savoircroissance()==100)
						{
							etrevivant[etrevivant_collision].changercroissance_termine(true);
							etrevivant[etrevivant_collision].changertaille(etrevivant[etrevivant_collision].savoirgene(1)*etrevivant[etrevivant_collision].savoircroissance()/100);
							etrevivant[etrevivant_collision].changerlargeur(sqrt(etrevivant[etrevivant_collision].savoirtaille()));
						}
						if(etrevivant[etrevivant_collision].savoircroissance()<100)
						{
							etrevivant[etrevivant_collision].changertaille(etrevivant[etrevivant_collision].savoirgene(1)*etrevivant[etrevivant_collision].savoircroissance()/100);
							etrevivant[etrevivant_collision].changerlargeur(sqrt(etrevivant[etrevivant_collision].savoirtaille()));
						}
						if(collision(etrevivant[etrevivanti].savoirx(),etrevivant[etrevivant_collision].savoirx(),etrevivant[etrevivanti].savoiry(),etrevivant[etrevivant_collision].savoiry(),etrevivant[etrevivanti].savoirlargeur(),etrevivant[etrevivant_collision].savoirlargeur(),etrevivant[etrevivanti].savoirlargeur(),etrevivant[etrevivant_collision].savoirlargeur(),0,1.1))
						{			
							// Verification de l'espèce (différente de ce qu'on considère comme semblable se nourrir ou ce qu'on considère comme semblable pour se reproduire)
							comparaison_genes=0;
							for(i=1;i<13;i++)
							{
								if(etrevivant[etrevivanti].savoirgene(i)!=0 && etrevivant[etrevivant_collision].savoirgene(i)!=0)
								{
									comparaison_genes+=(etrevivant[etrevivanti].savoirgene(i)>=etrevivant[etrevivant_collision].savoirgene(i) ? (etrevivant[etrevivanti].savoirgene(i)/etrevivant[etrevivant_collision].savoirgene(i)) : (etrevivant[etrevivant_collision].savoirgene(i)/etrevivant[etrevivanti].savoirgene(i)));
								}
								else
								{
									nombre_genes--;
								}
							}
							comparaison_genes/=nombre_genes;
									
							// Verification des conditions requises pour la reproduction
							if(etrevivant[etrevivanti].savoirreproduction_voulue() && etrevivant[etrevivanti].savoirtype()!=1 && etrevivant[etrevivant_collision].savoirtype()!=1 && etrevivant[etrevivant_collision].savoirreproduction_voulue() && comparaison_genes<=1+etrevivant[etrevivanti].savoirgene(11))
							{
								etrevivant[etrevivanti].reproduction(etrevivant_collision,etrevivant);
							}
									
							carnivore=etrevivant[etrevivanti].savoirgene(3)*hasard>=50;
							carnivore_collision=etrevivant[etrevivant_collision].savoirgene(3)*hasard>=50;
							// Verification des conditions requises pour se nourrir
							if(
							!etrevivant[etrevivanti].savoirreproduction_voulue() &&
															
							// Verification des alimentation ( carnivore ou herbivore ) et des genre ( végétal ou animal )
							((etrevivant[etrevivanti].savoirtype()==0 && ((etrevivant[etrevivant_collision].savoirtype()==0 && (carnivore || (!carnivore && carnivore_collision))) || (etrevivant[etrevivant_collision].savoirtype()==1 && !carnivore))) || (etrevivant[etrevivanti].savoirtype()==1 && etrevivant[etrevivant_collision].savoirtype()==1))
							)
							{
								energie_prise=(vitesse*etrevivant[etrevivanti].savoirtaille()/((etrevivant[etrevivanti].savoirtype()==1 && etrevivant[etrevivant_collision].savoirtype()==1) ? 10000 : (!carnivore && carnivore_collision ? 25000 : 1000))*(etrevivant[etrevivanti].savoirtype()==1 ? 1 : etrevivant[etrevivanti].savoirgene(2)*etrevivant[etrevivant_collision].savoircroissance()/100));
								if(etrevivant[etrevivanti].savoirtype()!=1 && etrevivant[etrevivant_collision].savoirtype()==0 && carnivore)
								{
									etrevivant[etrevivanti].changerventre(etrevivant[etrevivanti].savoirventre()+energie_prise);
									if(etrevivant[etrevivant_collision].savoirventre()<0)
									{
										etrevivant[etrevivanti].changerventre(etrevivant[etrevivanti].savoirventre()+etrevivant[etrevivant_collision].savoirventre());
										etrevivant[etrevivant_collision].changerventre(0);
									}
									if(etrevivant[etrevivanti].savoirventre()>etrevivant[etrevivanti].savoirtaille())
									{
										etrevivant[etrevivant_collision].changerventre(etrevivant[etrevivant_collision].savoirventre()+etrevivant[etrevivanti].savoirventre()-etrevivant[etrevivanti].savoirtaille());
										etrevivant[etrevivanti].changerventre(etrevivant[etrevivanti].savoirtaille());
									}
								}
								if(etrevivant[etrevivant_collision].savoirtype()==1 && !carnivore && etrevivant[etrevivanti].savoirtype()==0)
								{
									energie_prise=energie_prise>etrevivant[etrevivanti].savoirtaille()-etrevivant[etrevivanti].savoirventre() ? etrevivant[etrevivanti].savoirtaille()-etrevivant[etrevivanti].savoirventre() : energie_prise;
									fruit_mange=energie_prise/etrevivant[etrevivant_collision].savoirgene(12)>etrevivant[etrevivant_collision].savoirfruit() ? etrevivant[etrevivant_collision].savoirfruit() : energie_prise/etrevivant[etrevivant_collision].savoirgene(12);
									etrevivant[etrevivanti].changerventre(etrevivant[etrevivanti].savoirventre()+fruit_mange*etrevivant[etrevivant_collision].savoirgene(12));
									etrevivant[etrevivant_collision].changerfruit(etrevivant[etrevivant_collision].savoirfruit()-fruit_mange);
								}
								if((etrevivant[etrevivant_collision].savoirtype()==0 && etrevivant[etrevivanti].savoirtype()==0 && carnivore) || (etrevivant[etrevivant_collision].savoirtype()==1 && etrevivant[etrevivanti].savoirtype()==1))
								{
									etrevivant[etrevivant_collision].changerventre(etrevivant[etrevivant_collision].savoirventre()-energie_prise);
								}							
							}
						}
					}
				}
				if(!etrevivant[etrevivanti].savoircroissance_termine() && etrevivant[etrevivanti].savoircroissance()==100)
				{
					etrevivant[etrevivanti].changercroissance_termine(true);
					etrevivant[etrevivanti].changertaille(etrevivant[etrevivanti].savoirgene(1)*etrevivant[etrevivanti].savoircroissance()/100);
					etrevivant[etrevivanti].changerlargeur(sqrt(etrevivant[etrevivanti].savoirtaille()));
				}
				if(etrevivant[etrevivanti].savoircroissance()<100)
				{
					etrevivant[etrevivanti].changertaille(etrevivant[etrevivanti].savoirgene(1)*etrevivant[etrevivanti].savoircroissance()/100);
					etrevivant[etrevivanti].changerlargeur(sqrt(etrevivant[etrevivanti].savoirtaille()));
				}
				// autre
				if(etrevivant[etrevivanti].savoirtype()==1 && etrevivant[etrevivanti].savoirtemps_hasard_reproduction()+100<timer()*acceleration)
				{
					etrevivant[etrevivanti].changertemps_hasard_reproduction(timer()*acceleration);
					etrevivant[etrevivanti].changerhasard(((int)(((float)rand()/RAND_MAX)/10*((etrevivant[etrevivanti].savoirtaille()/etrevivant[etrevivanti].savoirgene(12))/etrevivant[etrevivanti].savoirfruit())))==0);
				}
				if(etrevivant[etrevivanti].savoirventre()>etrevivant[etrevivanti].savoirgene(6)+etrevivant[etrevivanti].savoirgene(5) && etrevivant[etrevivanti].prochain(etrevivant)!=-1 && etrevivant[etrevivanti].savoircroissance()>75 && max_etrevivant>=nb && (etrevivant[etrevivanti].savoirtype()!=1 || etrevivant[etrevivanti].savoirhasard())) etrevivant[etrevivanti].changerreproductionvoulue(true);
				if(etrevivant[etrevivanti].savoirventre()<etrevivant[etrevivanti].savoirgene(7)+etrevivant[etrevivanti].savoirgene(5) || etrevivant[etrevivanti].savoircroissance()<75 || etrevivant[etrevivanti].prochain(etrevivant)==-1 || max_etrevivant<nb) etrevivant[etrevivanti].changerreproductionvoulue(false);
				if(etrevivant[etrevivanti].savoirventre()<=0) etrevivant[etrevivanti].mort();
				if(etrevivant[etrevivanti].savoirsoif()<=0) etrevivant[etrevivanti].mort();
				if(etrevivant[etrevivanti].savoirsoif()<etrevivant[etrevivanti].savoirtaille()*1/4) etrevivant[etrevivanti].changerveut_boire(true);
				if(etrevivant[etrevivanti].savoirsoif()>=etrevivant[etrevivanti].savoirtaille()*3/4) etrevivant[etrevivanti].changerveut_boire(false);

				if(etrevivant[etrevivanti].savoircroissance()<100)
				{
					energie_prise=vitesse*etrevivant[etrevivanti].savoirgene(8)*((etrevivant[etrevivanti].savoirventre()/etrevivant[etrevivanti].savoirgene(9))>1 ? 1 : etrevivant[etrevivanti].savoirventre()/etrevivant[etrevivanti].savoirgene(9));
					etrevivant[etrevivanti].changercroissance(etrevivant[etrevivanti].savoircroissance()+energie_prise);
					etrevivant[etrevivanti].changerventre(etrevivant[etrevivanti].savoirventre()-energie_prise);
				}
				else if(etrevivant[etrevivanti].savoircroissance()>100)  etrevivant[etrevivanti].changercroissance(100);
				if(etrevivant[etrevivanti].savoirtype()==1)
				{
					etrevivant[etrevivanti].changerventre(etrevivant[etrevivanti].savoirventre()+etrevivant[etrevivanti].savoirtaille()*vitesse/2500);
					etrevivant[etrevivanti].changerfruit(etrevivant[etrevivanti].savoirfruit()+(etrevivant[etrevivanti].savoirtaille()*vitesse/5000)/etrevivant[etrevivanti].savoirgene(12));
					etrevivant[etrevivanti].changerventre(etrevivant[etrevivanti].savoirventre()-etrevivant[etrevivanti].savoirtaille()*vitesse/5000);				
				}
				else
				{
					etrevivant[etrevivanti].changerventre(etrevivant[etrevivanti].savoirventre()-(etrevivant[etrevivanti].savoirtaille()*etrevivant[etrevivanti].savoirgene(2)*etrevivant[etrevivanti].savoircroissance()/100*vitesse)/6000);
					etrevivant[etrevivanti].changersoif(etrevivant[etrevivanti].savoirsoif()-(etrevivant[etrevivanti].savoirtaille()*etrevivant[etrevivanti].savoirgene(2)*etrevivant[etrevivanti].savoircroissance()/100*vitesse)/6000);
				}
				if(etrevivant[etrevivanti].savoirtype()==1)
				{
					if(etrevivant[etrevivanti].savoirreproduction_voulue() && (timer()*acceleration-etrevivant[etrevivanti].savoirderniere_verification()>1000 || !etrevivant[etrevivant[etrevivanti].savoirchose_proche()].savoirvie()))
					{
						etrevivant[etrevivanti].changerderniere_verification(timer()*acceleration);
						etrevivant_collision=arbre_hasard(etrevivanti,etrevivant,1);
						etrevivant[etrevivanti].changerchose_proche(etrevivant_collision);
						if(etrevivant_collision!=etrevivanti && etrevivant[etrevivant_collision].savoirreproduction_voulue())
						{
							etrevivant[etrevivanti].reproduction(etrevivant_collision,etrevivant);
						}
					}
				}
				// verification pour savoir si l'etrevivant est sélectionné
				if(collision((etrevivant[etrevivanti].savoirx()-positionx)*zoom,xclic<=event.motion.x ? xclic : event.motion.x,(etrevivant[etrevivanti].savoiry()-positiony)*zoom,yclic<=event.motion.y ? yclic : event.motion.y,etrevivant[etrevivanti].savoirlargeur()*zoom,xclic<=event.motion.x ? event.motion.x-xclic : xclic-event.motion.x,etrevivant[etrevivanti].savoirlargeur()*zoom,yclic<=event.motion.y ? event.motion.y-yclic : yclic-event.motion.y,0) && clic && yclic<680 && event.motion.y<680)
				{
					etrevivant[etrevivanti].selectionner();
					if(ctrl) etrevivant_selectionne=etrevivanti;
					if(etrevivant_selectionne==-1) etrevivant_selectionne=etrevivanti;
				}
				if(etrevivant[etrevivanti].savoirventre()>etrevivant[etrevivanti].savoirtaille()) etrevivant[etrevivanti].changerventre(etrevivant[etrevivanti].savoirtaille());
				if(etrevivant[etrevivanti].savoirfruit()>etrevivant[etrevivanti].savoirtaille()/etrevivant[etrevivanti].savoirgene(12)) etrevivant[etrevivanti].changerfruit(etrevivant[etrevivanti].savoirtaille()/etrevivant[etrevivanti].savoirgene(12));
				if(etrevivant[etrevivanti].savoirsoif()>etrevivant[etrevivanti].savoirtaille()) etrevivant[etrevivanti].changersoif(etrevivant[etrevivanti].savoirtaille());
			}
		}	
		if(voir_genes_moyens)
		{
		for(i=1;i<13;i++)
			{
				genes_moyens[i]/=nb_animaux;
			}
		}

		
		//#include "traitement_unite.h"
		for(unitei=0;unitei<1000;unitei++)
		{
			if(unite[unitei].savoirvie())
			{
				if(vitesse_aret>100)
				{
					if(unite[unitei].savoirancienx()==unite[unitei].savoirx() && unite[unitei].savoirancieny()==unite[unitei].savoiry()) unite[unitei].changeraction(0);
					unite[unitei].changeranciennecoordonnees(unite[unitei].savoirx(),unite[unitei].savoiry());
					temps_aret=timer();
				}
				if(unite[unitei].savoiraction()==1)
				{
					unite[unitei].deplacement(unite[unitei].savoirdestination_finalex(),unite[unitei].savoirdestination_finaley(),unite[unitei].vitesse*vitesse);
				}				
				if((((unite[unitei].savoirx()-positionx)*zoom>xclic && (unite[unitei].savoirx()-positionx)*zoom<event.motion.x && xclic<event.motion.x) || ((unite[unitei].savoirx()-positionx)*zoom<xclic && (unite[unitei].savoirx()-positionx)*zoom>event.motion.x && xclic>event.motion.x)) && (((unite[unitei].savoiry()-positiony)*zoom>yclic && (unite[unitei].savoiry()-positiony)*zoom<event.motion.y && yclic<event.motion.y) || ((unite[unitei].savoiry()-positiony)*zoom<yclic && (unite[unitei].savoiry()-positiony)*zoom>event.motion.y && yclic>event.motion.y)) && clic && yclic<680 && event.motion.y<680)
				{ 
					unite[unitei].selectionner();
					type_selection=2;
				}
				for(i=0;i<1000;i++)
				{
					if(unite[i].savoirvie() && i!=unitei)
					{
						if(collision(unite[unitei].savoirx(),unite[i].savoirx(),unite[unitei].savoiry(),unite[i].savoiry(),unite[unitei].largeur,unite[i].largeur,unite[unitei].longueur,unite[i].longueur,0))
						{
							unite[unitei].deplacement(unite[unitei].savoirx()+(unite[unitei].savoirx()-unite[i].savoirx()),unite[unitei].savoiry()+(unite[unitei].savoiry()-unite[i].savoiry()),unite[unitei].vitesse*vitesse);
							if(collision(unite[unitei].savoirx(),unite[unitei].savoirdestination_finalex()-25,unite[unitei].savoiry(),unite[unitei].savoirdestination_finaley()-25,unite[unitei].largeur,50,unite[unitei].longueur,50,0)) unite[unitei].changeraction(0);
						}
					}
				}
				for(constructioni=0;constructioni<1000;constructioni++)
				{
					if(construction[constructioni].savoirvie())
					{
						if(collision(unite[unitei].savoirx(),construction[constructioni].savoirx(),unite[unitei].savoiry(),construction[constructioni].savoiry(),unite[unitei].largeur,construction[constructioni].largeur,unite[unitei].longueur,construction[constructioni].longueur,0))
						{
							unite[unitei].deplacement(unite[unitei].savoirx()+(unite[unitei].savoirx()-construction[constructioni].savoirx()),unite[unitei].savoiry()+(unite[unitei].savoiry()-construction[constructioni].savoiry()),unite[unitei].vitesse*vitesse);
						}
					}
				}
				for(etrevivant_collision=0;etrevivant_collision<5000;etrevivant_collision++)
				{
					if(etrevivant[etrevivant_collision].savoirvie())
					{
						if(!etrevivant[etrevivant_collision].savoircroissance_termine() && etrevivant[etrevivant_collision].savoircroissance()==100)
						{
							etrevivant[etrevivant_collision].changercroissance_termine(true);
							etrevivant[etrevivant_collision].changertaille(etrevivant[etrevivant_collision].savoirgene(1)*etrevivant[etrevivant_collision].savoircroissance()/100);
							etrevivant[etrevivant_collision].changerlargeur(sqrt(etrevivant[etrevivant_collision].savoirtaille()));
						}
						if(etrevivant[etrevivant_collision].savoircroissance()<100)
						{
							etrevivant[etrevivant_collision].changertaille(etrevivant[etrevivant_collision].savoirgene(1)*etrevivant[etrevivant_collision].savoircroissance()/100);
							etrevivant[etrevivant_collision].changerlargeur(sqrt(etrevivant[etrevivant_collision].savoirtaille()));
						}
						if(collision(unite[unitei].savoirx(),etrevivant[etrevivant_collision].savoirx(),unite[unitei].savoiry(),etrevivant[etrevivant_collision].savoiry(),unite[unitei].largeur,etrevivant[etrevivant_collision].savoirlargeur(),unite[unitei].longueur,etrevivant[etrevivant_collision].savoirlargeur(),0))
						{
							unite[unitei].deplacement(unite[unitei].savoirx()+(unite[unitei].savoirx()-etrevivant[etrevivant_collision].savoirx()),unite[unitei].savoiry()+(unite[unitei].savoiry()-etrevivant[etrevivant_collision].savoirx()),unite[unitei].vitesse*vitesse);
						}
					}
				}
			}
		}

		
		//#include "traitement_construction.h"
		for(constructioni=0;constructioni<1000;constructioni++)
		{
			if(construction[constructioni].savoirvie())
			{
				if(collision((construction[constructioni].savoirx()-positionx)*zoom,xclic<=event.motion.x ? xclic : event.motion.x,(construction[constructioni].savoiry()-positiony)*zoom,yclic<=event.motion.y ? yclic : event.motion.y,construction[constructioni].largeur*zoom,xclic<=event.motion.x ? event.motion.x-xclic : xclic-event.motion.x,construction[constructioni].longueur*zoom,yclic<=event.motion.y ? event.motion.y-yclic : yclic-event.motion.y,0) && clic && yclic<680 && event.motion.y<680)
				{ 
					construction[constructioni].selectionner();
					type_selection=1;
				}
						
				if(collision(20,xclic,740,yclic,20,1,20,1,1) && clic && temps_clic+1000<timer() && construction[constructioni].savoirselection())
				{ 
					construction[constructioni].construction_nouveau_unite(0,timer()*acceleration,type_unite,unite);
					temps_clic=timer();
				}
				construction[constructioni].construction_unite(0,timer()*acceleration,type_unite,unite,type_construction);
			}
		}

		
		//#include "affichage.h"
		SDL_FillRect(sEcran,&ecran,SDL_MapRGB(sEcran->format,0,0,0));
		affichage.x=0;
		affichage.y=0;
		affichage.w=1024;
		affichage.h=768;
		SDL_FillRect(sEcran,&affichage,SDL_MapRGB(sEcran->format,0,0,128));

		affichage.x=(int)((-1250-positionx)*zoom);
		affichage.y=(int)((-1250-positiony)*zoom);
		affichage.w=(int)(2900*zoom);
		affichage.h=(int)(2900*zoom);
		SDL_FillRect(sEcran,&affichage,SDL_MapRGB(sEcran->format,180,180,0));

		affichage.x=(int)((-1100-positionx)*zoom);
		affichage.y=(int)((-1100-positiony)*zoom);
		affichage.w=(int)(2600*zoom);
		affichage.h=(int)(2600*zoom);
		SDL_FillRect(sEcran,&affichage,SDL_MapRGB(sEcran->format,100,80,70));

		x=(int)((-300-positionx)*zoom);
		y=(int)((-300-positiony)*zoom);
		w=(int)(700*zoom);
		image(sEcran,lac,x,y,w,blanc);
		selectioni_arbre=0;
		selectioni_animaux=0;
		for(etrevivanti=0;etrevivanti<5000;etrevivanti++)
		{
			if(etrevivant[etrevivanti].savoirvie())
			{
				x=(int)((etrevivant[etrevivanti].savoirx()-positionx)*zoom);
				y=(int)((etrevivant[etrevivanti].savoiry()-positiony)*zoom);
				w=(int)(sqrt(etrevivant[etrevivanti].savoirgene(1)*etrevivant[etrevivanti].savoircroissance()/100)*zoom);
				switch(etrevivant[etrevivanti].savoirtype())
				{
					case 0:
						image(sEcran,singe,x,y,w,blanc);
					break;
					
					case 1:
						image(sEcran,arbre,x,y,w,blanc);
					break;
				}
				affichage.x=x;
				affichage.y=y;
				affichage.w=w;
				affichage.h=w;
				if(etrevivant[etrevivanti].savoirselection())
				{
					// Un carré jaune ou bleu autour de l'animal selectionné
					if(affichage.y+affichage.h<680 && affichage.y>0)
					{
						affichage.x-=affichage.w/2;
						affichage.y-=affichage.h/2;
						affichage.w*=2;
						affichage.h=1;
						SDL_FillRect(sEcran,&affichage,etrevivanti==etrevivant_selectionne ? bleu : jaune);
						
						affichage.y+=affichage.w;
						SDL_FillRect(sEcran,&affichage,etrevivanti==etrevivant_selectionne ? bleu : jaune);
						
						
						affichage.y-=affichage.w;
						affichage.h=affichage.w;
						affichage.w=1;
						SDL_FillRect(sEcran,&affichage,etrevivanti==etrevivant_selectionne ? bleu : jaune);
						
						affichage.x+=affichage.h;
						SDL_FillRect(sEcran,&affichage,etrevivanti==etrevivant_selectionne ? bleu : jaune);
					}
					
					
					if(etrevivant[etrevivanti].savoirtype()) selectioni_arbre++; else selectioni_animaux++;
					affichage.x=512+15*(etrevivant[etrevivanti].savoirtype() ? selectioni_arbre : selectioni_animaux);
					affichage.y=etrevivant[etrevivanti].savoirtype() ? 690 : 710;
					affichage.w=10;
					affichage.h=affichage.w;
					if(collision(affichage.x,xclic<=event.motion.x ? xclic : event.motion.x,affichage.y,yclic<=event.motion.y ? yclic : event.motion.y,10,xclic<=event.motion.x ? event.motion.x-xclic : xclic-event.motion.x,10,yclic<=event.motion.y ? event.motion.y-yclic : yclic-event.motion.y,0) && clic && yclic>680 && event.motion.y>680)
					{
						etrevivant_selectionne=etrevivanti;
					}

					SDL_FillRect(sEcran,&affichage,etrevivant[etrevivanti].savoirtype()==1 ? SDL_MapRGB(sEcran->format,0,255,0) :SDL_MapRGB(sEcran->format,255,(int)((double)(100-etrevivant[etrevivanti].savoirgene(3))/100*255),(int)((double)(100-etrevivant[etrevivanti].savoirgene(3))/100*255)));
					if(etrevivanti==etrevivant_selectionne)
					{
						affichage.x-=affichage.w/2;
						affichage.y-=affichage.h/2;
						affichage.w*=2;
						affichage.h=1;
						SDL_FillRect(sEcran,&affichage,bleu);
						
						affichage.y+=affichage.w;
						SDL_FillRect(sEcran,&affichage,bleu);
							
							
						affichage.y-=affichage.w;
						affichage.h=affichage.w;
						affichage.w=1;
						SDL_FillRect(sEcran,&affichage,bleu);
							
						affichage.x+=affichage.h;
						SDL_FillRect(sEcran,&affichage,bleu);
					}				
				}			
			}
		}
		selectioni_unite=0;
		selectioni_construction=0;
		for(unitei=0;unitei<1000;unitei++)
		{
			if(unite[unitei].savoirvie())
			{
				affichage.x=(int)((unite[unitei].savoirx()-positionx)*zoom);
				affichage.y=(int)((unite[unitei].savoiry()-positiony)*zoom);
				affichage.w=(int)(unite[unitei].largeur*zoom);
				affichage.h=(int)(unite[unitei].longueur*zoom);
				SDL_FillRect(sEcran,&affichage,SDL_MapRGB(sEcran->format,128,128,128));
				if(unite[unitei].savoirselection())
				{
					selectioni_unite++;
					affichage.x=512+15*selectioni_unite;
					affichage.y=730;
					affichage.w=(int)(unite[unitei].largeur);
					affichage.h=(int)(unite[unitei].longueur);
					SDL_FillRect(sEcran,&affichage,SDL_MapRGB(sEcran->format,128,128,128));
				}		
			}
		}
			
		for(constructioni=0;constructioni<1000;constructioni++)
		{
			if(construction[constructioni].savoirvie())
			{
				affichage.x=(int)((construction[constructioni].savoirx()-positionx)*zoom);
				affichage.y=(int)((construction[constructioni].savoiry()-positiony)*zoom);
				affichage.w=(int)(construction[constructioni].largeur*zoom);
				affichage.h=(int)(construction[constructioni].longueur*zoom);
				SDL_FillRect(sEcran,&affichage,SDL_MapRGB(sEcran->format,128,128,0));
				if(construction[constructioni].savoirselection())
				{
					selectioni_construction++;
					affichage.x=512+15*selectioni_construction;
					affichage.y=750;
					affichage.w=10;
					affichage.h=10;
					SDL_FillRect(sEcran,&affichage,SDL_MapRGB(sEcran->format,128,128,0));
				}
			}
		}
		if(selectioni_construction!=0)
		{
			affichage.x=20;
			affichage.y=740;
			affichage.w=20;
			affichage.h=20;
			SDL_FillRect(sEcran,&affichage,SDL_MapRGB(sEcran->format,0,255,0));
		}
		// rectangle de sélection
		if(clic && yclic<680 &&((yclic<event.motion.y && yclic+(event.motion.y-yclic)<680) || event.motion.y<yclic ))
		{
			affichage.y=yclic;
			affichage.h=1;
			if(xclic<event.motion.x)
			{
				affichage.x=xclic;
					affichage.w=(event.motion.x-xclic);
			}
			else
			{
				affichage.x=event.motion.x;
					affichage.w=(xclic-event.motion.x);
				
			}
			SDL_FillRect(sEcran,&affichage,SDL_MapRGB(sEcran->format,255,255,255));
			affichage.y=event.motion.y;
			SDL_FillRect(sEcran,&affichage,SDL_MapRGB(sEcran->format,255,255,255));
			if(yclic<event.motion.y)
			{
				affichage.y=yclic;
				affichage.h=(event.motion.y-yclic);
			}
			else
			{
				affichage.y=event.motion.y;
				affichage.h=(yclic-event.motion.y);
			}
			affichage.w=1;
			SDL_FillRect(sEcran,&affichage,SDL_MapRGB(sEcran->format,255,255,255));
			if(xclic<event.motion.x) affichage.x=event.motion.x;
			else affichage.x=xclic;
			SDL_FillRect(sEcran,&affichage,SDL_MapRGB(sEcran->format,255,255,255));	
		}
		if(etrevivant_selectionne!=-1)
		{
			ecriture.Text(700,marge+40,sEcran,false,"Numero: %d",etrevivant_selectionne);
			ecriture.Text(700,marge+60,sEcran,false,"En vie: %d",etrevivant[etrevivant_selectionne].savoirvie());
			ecriture.Text(700,marge+80,sEcran,false,"Reproduction voulue: %d",etrevivant[etrevivant_selectionne].savoirreproduction_voulue());
			ecriture.Text(700,marge+100,sEcran,false,"Ventre: %d",(int)etrevivant[etrevivant_selectionne].savoirventre());
			ecriture.Text(700,marge+120,sEcran,false,"Soif: %d",(int)etrevivant[etrevivant_selectionne].savoirsoif());
			ecriture.Text(700,marge+140,sEcran,false,"Fruit: %d",(int)etrevivant[etrevivant_selectionne].savoirfruit());
			ecriture.Text(700,marge+160,sEcran,false,"Numero de la chose en approche: %d",etrevivant[etrevivant_selectionne].savoirchose_proche());
			ecriture.Text(700,marge+180,sEcran,false,"Croissance: %d/100",(int)etrevivant[etrevivant_selectionne].savoircroissance());
			ecriture.Text(700,marge+200,sEcran,false,"Genes :");
			for(i=1;i<13;i++)
			{	
				ecriture.Text(700,marge+200+20*i,sEcran,false,"%s :%d",nom_gene[i],(int)etrevivant[etrevivant_selectionne].savoirgene(i));
			}
			if(bouton(20,720,20,20,clic,xclic,yclic,sEcran,SDL_MapRGB(sEcran->format,0,0,0))) etrevivant[etrevivant_selectionne].mort();
		}
			
		ecriture.Text(700,10,sEcran,false,(zoom>=1) ? "Zoom : %dX" : "Zoom : %d/1000",(zoom>=1) ? (int)zoom : (int)(zoom*1000));
		heure=(int)(timer()/1000/3600);
		minute=(int)(timer()/1000/60-60*heure);
		seconde=(int)(timer()/1000-60*(minute+heure*60));
		ecriture.Text(700,30,sEcran,false,"Temps depuis lancee: %d h %d m %d s",heure,minute,seconde);
		ecriture.Text(700,50,sEcran,false,"Nombre d'animaux maximum: %d",(int)max_etrevivant);
		ecriture.Text(700,70,sEcran,false,"Nombre d'animaux: %d",nb_animaux);		
		ecriture.Text(700,90,sEcran,false,"Vitesse: %d",(int)(vitesse_speciale*1000));
		ecriture.Text(700,110,sEcran,false,"Acceleration: %d",(int)acceleration);
		ecriture.Text(700,130,sEcran,false,"Nombre d'etre vivant: %d",nb);	
		if(!voir_genes_moyens && bouton(1004,20,20,20,clic,xclic,yclic,sEcran,SDL_MapRGB(sEcran->format,128,0,128))) voir_genes_moyens=true;
		if(voir_genes_moyens && bouton(1004,50,20,20,clic,xclic,yclic,sEcran,SDL_MapRGB(sEcran->format,128,0,0))) voir_genes_moyens=false;
		if(voir_genes_moyens)
		{
			affichage.x=20;
			affichage.y=20;
			affichage.w=330;
			affichage.h=300;
			SDL_FillRect(sEcran,&affichage,SDL_MapRGB(sEcran->format,0,128,0));
			ecriture.Text(30,40,sEcran,false,"Genes Moyens des animaux :");
			for(i=1;i<13;i++)
			{
				ecriture.Text(30,60+20*i,sEcran,false,"%s :%d",nom_gene[i],(int)genes_moyens[i]);
			}
		}
		SDL_Flip(sEcran);

		
		//SDL_Flip(lac_.afficher(104));
	}
	return 0;
}
