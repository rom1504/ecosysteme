#include "objet.h"

class Type_unite
{
	public:
		double largeur,longueur,vitesse,portee,temps_construction,attaque,defense,energie_maximale;
	public:
		void creation(double largeur,double longueur,double vitesse,double portee,double attaque,double defense,double energie_maximale,double temps_construction);
};

class Unite:public Objet
{
	protected:
		double destination_finalex,destination_finaley,destinationx,destinationy,ancienx,ancieny,energie;
		int action;
	public:
		double largeur,longueur,vitesse,portee,temps_construction,attaque,defense,energie_maximale;
		void creation(double x,double y,double energie,int type,Type_unite *type_unite);
		double savoirdestination_finalex();
		double savoirdestination_finaley();
		double savoirdestinationx();
		double savoirdestinationy();
		double savoirancienx();
		double savoirancieny();
		int savoiraction();
		void changeraction(int action);
		void changerdestinationfinale(double destination_finalex,double destination_finaley);
		void changerdestination(double destinationx,double destinationy);
		void changeranciennecoordonnees(double ancienx,double ancieny);
};
