#include "objet.h"
#include "trigonometrie.h"

bool Objet::savoirselection()
{
	return selection;
}

int Objet::savoirtype()
{
	return type;
}

double Objet::savoirx()
{
	return x;
}

double Objet::savoiry()
{
	return y;
}

double Objet::savoirangle()
{
	return angle;
}

bool Objet::savoirvie()
{
	return vie;
}

void Objet::selectionner()
{
	selection=true;
}

void Objet::deselectionner()
{
	selection=false;
}

void Objet::deplacement(double trajectoire_x,double trajectoire_y,double vitesse)
{
	double deplacement_totalx,deplacement_totaly,deplacement_actuelx,deplacement_actuely;
	deplacement_totalx=trajectoire_x-x;				
	deplacement_totaly=trajectoire_y-y;
	angle=atan_degre(abs((deplacement_totaly==0) ? 1 : deplacement_totaly)/abs((deplacement_totalx==0) ? 1 : deplacement_totalx));
	deplacement_actuelx=(deplacement_totalx>=0 ? 1 : -1)*cos_degre(angle)*vitesse;
	if(abs(deplacement_actuelx)>abs(deplacement_totalx)) deplacement_actuelx=deplacement_totalx;
	x+=deplacement_actuelx;					
	deplacement_actuely=(deplacement_totaly>=0 ? 1 : -1)*sin_degre(angle)*vitesse;
	if(abs(deplacement_actuely)>abs(deplacement_totaly)) deplacement_actuely=deplacement_totaly;
	y+=deplacement_actuely;
}

void Objet::changerx(double x)
{
	this->x=x;
}

void Objet::changery(double y)
{
	this->y=y;
}
