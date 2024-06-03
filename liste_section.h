#ifndef LISTE_SECTION_H /* garde d'inclusion */
#define LISTE_SECTION_H

#include<stdlib.h>
typedef struct{
	unsigned taille;
	unsigned couleur;
	void* suite;
	char direction;
} Section;

Section* Allouer_Section(unsigned t,unsigned c,char direction);
void Desallouer_Section(Section*);


#endif
