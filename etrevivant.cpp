#include "objet.h"
#include "etrevivant.h"
#include <math.h>
double timer();
bool collision(double x1,double x2,double y1,double y2,double w1,double w2,double h1,double h2,bool type_comparaison,double marge);
bool collision(double x1,double x2,double y1,double y2,double w1,double w2,double h1,double h2,bool type_comparaison);

void Etrevivant::creation(double gene1,double gene2,double gene3,double gene4,double gene5,double gene6,double gene7,double gene8,double gene9,double gene10,double gene11,double gene12,double x,double y,double ventre,int type,double croissance,double soif,double fruit,double energie)
{
	this->genes[1]=gene1;this->genes[2]=gene2;this->genes[3]=gene3;this->genes[4]=gene4;this->genes[5]=gene5;this->genes[6]=gene6;this->genes[7]=gene7;this->genes[8]=gene8;this->genes[9]=gene9;this->genes[10]=gene10;this->genes[11]=gene11;this->genes[12]=gene12;
	vie=true;
	reproduction_voulue=false;
	veut_boire=false;
	chose_proche=-1;
	derniere_verification=0;
	angle=0;
	largeur=-1;
	taille=-1;
	croissance_termine=false;
	temps_hasard_reproduction=0;
	temps_collision=0;
	this->fruit=fruit;
	hasard=false;
	this->x=x;
	this->y=y;
	this->ventre=ventre;
	this->energie=energie;	
	this->type=type;
	this->croissance=croissance;
	this->soif=soif;
}

double myrand()
{
	double i=1;
	while(true) if((int)(((float)rand()/RAND_MAX)*2)!=0) break; else i=(int)(((float)rand()/RAND_MAX)*2)!=0 ? i*1.1 : i/1.1;
	return i;
}

void Etrevivant::reproduction(int partenaire,Etrevivant *etrevivant)
{
	if(this->genes[5]<this->ventre  && etrevivant[partenaire].genes[5]<etrevivant[partenaire].ventre && etrevivant[partenaire].croissance>75 && this->croissance>75)
	{
		int i,prochain=this->prochain(etrevivant),type,xterrain=-1100,yterrain=-1100,largeurterrain=2600,hauteurterrain=2600,etrevivant_collision;
		double genes[13],croissance,ventre,x,y,soif,largeur,largeur_lui,largeur_partenaire;
		bool creation=true;
		if(prochain!=-1)
		{
			for(i=1;i<13;i++)
			{
				if(this->genes[i]!=0 && etrevivant[partenaire].genes[i]!=0)
				{
					genes[i]=(this->genes[i]+etrevivant[partenaire].genes[i])/2*myrand();
				}
				else
				{
					genes[i]=0;
				}
			}
			largeur_lui=sqrt(this->genes[1]);
			largeur_partenaire=sqrt(etrevivant[partenaire].genes[1]);
			croissance=((this->genes[10]+etrevivant[partenaire].genes[10])/2>100 ? 100 : (this->genes[10]+etrevivant[partenaire].genes[10])/2);
			double hasardx,hasardy,plus_gros=(int)(largeur_lui>=largeur_partenaire ? largeur_lui : largeur_partenaire)*5;
			switch((int)(((double)rand()/RAND_MAX)*4))
			{
				case 0:
				hasardx=plus_gros;
				hasardy=0;
				break;
				case 1:
				hasardx=-plus_gros;
				hasardy=0;
				break;
				case 2:
				hasardx=0;
				hasardy=plus_gros;
				break;
				case 3:
				hasardx=0;
				hasardy=-plus_gros;
				break;
			}
			ventre=this->genes[5]+etrevivant[partenaire].genes[5];
			if(ventre>croissance/100*genes[1]) ventre=croissance/100*genes[1];
			soif=this->genes[5]+etrevivant[partenaire].genes[5];
			if(soif>croissance/100*genes[1]) soif=croissance/100*genes[1];
			x=(this->x+etrevivant[partenaire].x)/2+hasardx;
			y=(this->y+etrevivant[partenaire].y)/2+hasardy;
			largeur=sqrt(genes[1]);
			x=x+largeur>xterrain+largeurterrain ? xterrain+largeurterrain-largeur : x;
			y=y+largeur>yterrain+hauteurterrain ? yterrain+hauteurterrain-largeur : y;
			x=x<xterrain ? xterrain : x;
			y=y<yterrain ? yterrain : y;
			x=x+largeur>-500 && x<700 && y+largeur>-500 && y<700 ? -500-largeur : x;
			type=this->type;
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
					if(collision(x,etrevivant[etrevivant_collision].savoirx(),y,etrevivant[etrevivant_collision].savoiry(),largeur,etrevivant[etrevivant_collision].savoirlargeur(),largeur,etrevivant[etrevivant_collision].savoirlargeur(),0))
					{
						creation=false;
					}
				}
			}
			if(creation)
			{
				etrevivant[prochain].creation(genes[1],genes[2],genes[3],genes[4],genes[5],genes[6],genes[7],genes[8],genes[9],genes[10],genes[11],genes[12],x,y,ventre,type,croissance,soif,0,100);
				this->ventre-=this->genes[5];
				etrevivant[partenaire].ventre-=etrevivant[partenaire].genes[5];
				this->reproduction_voulue=false;
				etrevivant[partenaire].reproduction_voulue=false;
			}
		}
		else
		{
			this->reproduction_voulue=false;
			etrevivant[partenaire].reproduction_voulue=false;
		}
	}
}



int Etrevivant::prochain(Etrevivant *etrevivant)
{		

	int i,prochain=-1;
	for (i=0;i<5000;i++)
	{
		if(etrevivant[i].vie==false)
		{
			prochain=i;
			break;
		}
	}
	return prochain;
}

void Etrevivant::mort()
{
	int i;
	for(i=1;i<13;i++)
	{
		genes[i]=0;
	}
	vie=false;
}

double Etrevivant::savoirgene(int gene)
{
	return genes[gene];
}

double Etrevivant::savoirderniere_verification()
{
	return derniere_verification;
}

double Etrevivant::savoirfruit()
{
	return fruit;
}

int Etrevivant::savoirchose_proche()
{
	return chose_proche;
}

bool Etrevivant::savoirreproduction_voulue()
{
	return reproduction_voulue;
}

bool Etrevivant::savoirhasard()
{
	return hasard;
}

bool Etrevivant::savoirveut_boire()
{
	return veut_boire;
}

void Etrevivant::changerderniere_verification(double derniere_verification)
{
	this->derniere_verification=derniere_verification;
}

void Etrevivant::changerfruit(double fruit)
{
	this->fruit=fruit;
}

void Etrevivant::changerchose_proche(int chose_proche)
{
	this->chose_proche=chose_proche;
}

double Etrevivant::savoircroissance()
{
	return croissance;
}

double Etrevivant::savoirventre()
{
	return ventre;
}

double Etrevivant::savoirenergie()
{
	return energie;
}

double Etrevivant::savoirsoif()
{
	return soif;
}

bool Etrevivant::savoircroissance_termine()
{
	return croissance_termine;
}

double Etrevivant::savoirtaille()
{
	return taille;
}

double Etrevivant::savoirlargeur()
{
	return largeur;
}

double Etrevivant::savoirtemps_collision()
{
	return temps_collision;
}

double Etrevivant::savoirtemps_hasard_reproduction()
{
	return temps_hasard_reproduction;
}

void Etrevivant::changertemps_hasard_reproduction(double temps_hasard_reproduction)
{
	this->temps_hasard_reproduction=temps_hasard_reproduction;
}

void Etrevivant::changertemps_collision(double temps_collision)
{
	this->temps_collision=temps_collision;
}

void Etrevivant::changersoif(double soif)
{
	this->soif=soif;
}

void Etrevivant::changerventre(double ventre)
{
	this->ventre=ventre;
}

void Etrevivant::changerenergie(double energie)
{
	this->energie=energie;
}

void Etrevivant::changercroissance(double croissance)
{
	this->croissance=croissance;
}

void Etrevivant::changertaille(double taille)
{
	this->taille=taille;
}

void Etrevivant::changerlargeur(double largeur)
{
	this->largeur=largeur;
}

void Etrevivant::changercroissance_termine(bool croissance_termine)
{
	this->croissance_termine=croissance_termine;
}

void Etrevivant::changerreproductionvoulue(bool reproductionvoulue)
{
	this->reproduction_voulue=reproductionvoulue;
}

void Etrevivant::changerveut_boire(bool veut_boire)
{
	this->veut_boire=veut_boire;
}

void Etrevivant::changerhasard(bool hasard)
{
	this->hasard=hasard;
}

