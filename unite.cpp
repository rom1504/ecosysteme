#include "unite.h"

void Type_unite::creation(double largeur,double longueur,double vitesse,double portee,double attaque,double defense,double energie_maximale,double temps_construction)
{
	this->largeur=largeur;
	this->longueur=longueur;
	this->vitesse=vitesse;
	this->portee=portee;
	this->attaque=attaque;
	this->defense=defense;
	this->energie_maximale=energie_maximale;
	this->temps_construction=temps_construction;
}

void Unite::creation(double x,double y,double energie,int type,Type_unite *type_unite)
{
	vie=true;
	selection=0;
	action=0;
	this->x=x;
	this->y=y;
	this->energie=energie;
	this->type=type;
	largeur=type_unite[type].largeur;
	longueur=type_unite[type].longueur;
	vitesse=type_unite[type].vitesse;
	portee=type_unite[type].portee;
	attaque=type_unite[type].attaque;
	defense=type_unite[type].defense;
	energie_maximale=type_unite[type].energie_maximale;
}

void Unite::changerdestinationfinale(double destination_finalex,double destination_finaley)
{
	action=1;
	this->destination_finalex=destination_finalex;
	this->destination_finaley=destination_finaley;
}

void Unite::changerdestination(double destinationx,double destinationy)
{
	action=1;
	this->destinationx=destinationx;
	this->destinationy=destinationy;
}

void Unite::changeranciennecoordonnees(double ancienx,double ancieny)
{
	this->ancienx=ancienx;
	this->ancieny=ancieny;
}

void Unite::changeraction(int action)
{
	this->action=action;
}

double Unite::savoirdestination_finalex()
{
	return destination_finalex;
}

double Unite::savoirdestination_finaley()
{
	return destination_finaley;
}

double Unite::savoirdestinationx()
{
	return destinationx;
}

double Unite::savoirdestinationy()
{
	return destinationy;
}

double Unite::savoirancienx()
{
	return ancienx;
}

double Unite::savoirancieny()
{
	return ancieny;
}

int Unite::savoiraction()
{
	return action;
}
