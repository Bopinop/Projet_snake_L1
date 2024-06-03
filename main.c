#include"grille.h"
#include"serpent.h"
#include"interface.h"
#include<stdio.h>


int main(int argc, char** argv)
{
	unsigned n=10;
	unsigned m=10;
	unsigned c=255000;
	char bouboul=0;

	selection_for_main(argc,argv,&n,&m,&c,&bouboul);
	Grille* g= Grille_allouer(n,m);
	Grille_vider(g);

	Serpent* se=Creer_Serpent(n/2,m/2);
	Section* s= Allouer_Section(1,c,1);
	ajouter_section_debut(se,s);

	Grille_tirage_fruit(g,se);
	Grille_remplir(g,se);
	Grille_redessiner(g);
	Create_picture(g,se,bouboul);
	Grille_desallouer(g);
	desallouer_Serpent(se);
	return 0;
}
