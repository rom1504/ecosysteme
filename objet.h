#include <stdio.h>
#include <stdlib.h>

double abs(double nombre);

class Objet
{
	protected:
		double x,y,angle;
		bool selection,vie;
		int type;
		
	public:
		Objet() {}
		bool savoirselection();
		int savoirtype();
		double savoirx();
		double savoiry();
		void changerx(double x);
		void changery(double y);
		double savoirangle();
		void deplacement(double trajectoire_x,double trajectoire_y,double vitesse);
		bool savoirvie();
		void selectionner();
		void deselectionner();
};
