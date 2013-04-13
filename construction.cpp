#include "construction.h"

void Type_construction::creation(double largeur,double longueur,double portee,double attaque,double defense,double energie_maximale,double temps_construction)
{
	this->largeur=largeur;
	this->longueur=longueur;
	this->portee=portee;
	this->attaque=attaque;
	this->defense=defense;
	this->energie_maximale=energie_maximale;
	this->temps_construction=temps_construction;
}

void Construction::creation(double x,double y,double energie,int type,double emplacement_unitesx,double emplacement_unitesy,Type_construction *type_construction)
{
	int i;
	for(i=0;i<100;i++) action[i]=-1;
	selection=0;
	this->x=x;
	this->y=y;
	this->energie=energie;
	this->type=type;
	this->emplacement_unitesx=emplacement_unitesx;
	this->emplacement_unitesy=emplacement_unitesy;
	vie=true;
	largeur=type_construction[type].largeur;
	longueur=type_construction[type].longueur;
	portee=type_construction[type].portee;
	attaque=type_construction[type].attaque;
	defense=type_construction[type].defense;
	energie_maximale=type_construction[type].energie_maximale;
}

Construction::Construction()
{
	derniere_action=0;
	construction_en_cours=0;
	vie=0;
}
int Construction::prochain(double time,Type_unite *type_unite,Unite *unite)
{		
	int i,prochain=-1;
	for (i=0;i<100;i++)
	{
		if(!unite[i].savoirvie() && action[i]==-1)
		{
			prochain=i;
			break;
		}
		else if(i==99) prochain=-1;
		
	}
	return prochain;
}
int Construction::construction_nouveau_unite(int type,double time,Type_unite *type_unite,Unite *unite)
{
	action[prochain(time,type_unite,unite)]=type;
	temps_debut_construction=time;
	return 0; // inutile
}
void Construction::construction_unite(int type,double time,Type_unite *type_unite,Unite *unite,Type_construction * type_construction)
{
	int i;
	for(i=0;i<100;i++)
	{	
		if(action[i]!=-1)
		{
			if(time-temps_debut_construction>type_unite[type].temps_construction)
			{
				unite[prochain(time,type_unite,unite)].creation(emplacement_unitesx,emplacement_unitesy,type_construction[type].energie_maximale,type,type_unite);
				action[i]=-1;
				temps_debut_construction=time;
			}
		}
	}
}
