#include"liste_section.h"

Section* Allouer_Section(unsigned t, unsigned c,char d)
{
	Section* s=malloc(sizeof(Section));
	s->taille=t;
	s->couleur=c;
	s->suite=NULL;
	s->direction=d;
	return s;
}

void Desallouer_Section(Section* s)
{
	free(s);
}
