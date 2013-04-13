/*
Gènes:
1: Taille maximale
2: Vitesse maximale
3: Agressivité(herbivore,omnivore ou carnivore) , de plus de 0 à 100
4: Distance d'aparition du nouveau arbre par rapport à la moyenne entre les positions du premier et du deuxième arbre
5: Utilisation d'énergie pour la reproduction ( et donc le "bébé" aura l'énergie des deux "parents" à la naissance )
6: Energie à partir de la quelle la reproduction est recherchée ( en ajoutant l'energie nécéssaire pour la reproduction : voir gène 5 )
7: Energie à partir de la quelle la reproduction n'est plus recherchée ( en ajoutant l'energie nécéssaire pour la reproduction : voir gène 5 )
8: Facteur de croissance: Quand la croissance se produit la vitesse et la taille sont multipliés par ce facteur( en fonction de l'energie disponible )
9: Energie nécéssaire au mieux pour la croissance ( la croissance existe si cette energie n'est pas atteinte mais elle est moins importante )
10: Croissance à la naissance, de plus de 0 à 100
11: Compatibilité pour la reproduction, de plus de 0 à 100
12: Taille des fruits
*/
double myrand();
class Etrevivant:public Objet
{
	protected:
		int chose_proche;
		double energie,ventre,genes[13],derniere_verification,croissance,soif,fruit,largeur,taille,temps_collision,temps_hasard_reproduction;
		bool reproduction_voulue,veut_boire,hasard,croissance_termine;
	
	public:
		void reproduction(int partenaire,Etrevivant *etrevivant);
		int prochain(Etrevivant *etrevivant);
		void mort();
		void creation(double gene1,double gene2,double gene3,double gene4,double gene5,double gene6,double gene7,double gene8,double gene9,double gene10,double gene11,double gene12,double x,double y,double ventre,int type,double croissance,double soif,double fruit,double energie);
		double savoirgene(int gene);
		double savoirderniere_verification();
		int savoirchose_proche();
		bool savoirreproduction_voulue();
		bool savoirveut_boire();
		bool savoirhasard();
		bool savoircroissance_termine();
		double savoircroissance();
		double savoirventre();
		double savoirenergie();
		double savoirsoif();
		double savoirfruit();
		double savoirtaille();
		double savoirlargeur();
		double savoirtemps_collision();
		double savoirtemps_hasard_reproduction();
		void changertemps_hasard_reproduction(double temps_hasard_reproduction);	
		void changertemps_collision(double temps_collision);		
		void changerderniere_verification(double derniere_verification);
		void changerchose_proche(int chose_proche);
		void changerventre(double ventre);
		void changersoif(double soif);
		void changerreproductionvoulue(bool reproductionvoulue);
		void changerveut_boire(bool veut_boire);
		void changerhasard(bool hasard);
		void changercroissance(double croissance);
		void changerfruit(double fruit);
		void changerenergie(double energie);
		void changertaille(double taille);
		void changerlargeur(double largeur);
		void changercroissance_termine(bool croissance_termine);
};
