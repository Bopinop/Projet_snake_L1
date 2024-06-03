#ifndef SERPENT_H /* garde d'inclusion */
#define SERPENT_H
#include"liste_section.h"

typedef struct Serpent{
	unsigned x;
	unsigned y;
	Section* debut;
	Section* fin;
	unsigned x_f;
	unsigned y_f;
}Serpent;

Serpent* Creer_Serpent(unsigned x, unsigned y);
void ajouter_section_debut(Serpent*,Section*);
void ajouter_section_fin(Serpent*,Section*);
void desallouer_Serpent(Serpent*);
Section* retire_section_debut(Serpent*);
unsigned l_total(Serpent* se);
 

#endif
