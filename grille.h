#ifndef GRILLE_H /* garde d'inclusion */
#define GRILLE_H
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include"serpent.h"
typedef struct Grille{
	unsigned int m;
	unsigned int n;
	char*** tab;

	unsigned int C1;
	unsigned int C2;
}Grille;

Grille* Grille_allouer(unsigned n, unsigned m);
void Grille_vider(Grille* g);
void Grille_tirage_fruit(Grille* g,Serpent*);
void Grille_remplir(Grille* g,Serpent*);
void Grille_desallouer(Grille* g);
void Grille_redessiner(Grille* g);
void str_e8(char*,const char*);
void str_c2(char*,const unsigned);
int str_cmp(char* c2,char* c1);
int power(int n,int p);
#endif
