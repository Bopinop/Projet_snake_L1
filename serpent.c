#include"serpent.h"
/*initialise un serpent
 */
Serpent* Creer_Serpent(unsigned x,unsigned y)
{
	Serpent* se=malloc(sizeof(Serpent));
	se->x=x;
	se->y=y;
	se->debut=NULL;
	se->fin=NULL;
	se->x_f=x;
	se->y_f=y+1;
	return se;
}
/*
 *ajoute une section au début
 */
void ajouter_section_debut(Serpent* se, Section* s)
{
	if(!se->fin)
		se->fin=s;
	Section* d=se->debut;
	se->debut=s;
	s->suite=d;
}
/*regarde la longeur de le liste du serpent
 */
unsigned l_total(Serpent* se)
{
	Section* s=se->debut;
	unsigned l=0;
	while(s)
	{
		l+=s->taille;
		s=s->suite;
	}
	return l;
}
/*ajoute à la fin de la section
 */
void ajouter_section_fin(Serpent* se, Section* s)
{
	if(!se->debut)
		se->debut=s;
	Section* d=se->fin;
	se->fin=s;
	d->suite=s;
}
/*desaloue un serpent
 */
void desallouer_Serpent(Serpent* se)
{
	Section* s=(se)->debut;
	while(s)
	{
		Section* temp=s;
		s=s->suite;
		free(temp);
	}
	free(se);
}
/*retire la section du debut
 */
Section* retire_section_debut(Serpent* se)
{
	Section* s=se->debut;
	if(!s->suite)
		se->fin=s->suite;
	se->debut=s->suite;
	s->suite=NULL;
	return s;
}
