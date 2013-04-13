#include "unite.h"

class Type_construction
{
	public:
		double largeur,longueur,portee,temps_construction,energie_maximale,defense,attaque;
		void creation(double largeur,double longueur,double portee,double attaque,double defense,double energie_maximale,double temps_construction);
};

class Construction:public Objet
{
	protected:
		double emplacement_unitesx,emplacement_unitesy,temps_debut_construction,energie;
		int action[100],derniere_action;
		bool construction_en_cours,etat,selection;
		
	
	public:
		double largeur,longueur,portee,temps_construction,energie_maximale,defense,attaque;
		int prochain(double time,Type_unite *type_unite,Unite *unite);
		int construction_nouveau_unite(int type,double time,Type_unite *type_unite,Unite *unite);
		void construction_unite(int type,double time,Type_unite *type_unite,Unite *unite,Type_construction * type_construction);
		void creation(double x,double y,double energie,int type,double emplacement_unitesx,double emplacement_unitesy,Type_construction *type_construction);
		Construction();
};
