#include"grille.h"

/*alloue une grille
 */
Grille* Grille_allouer(unsigned n, unsigned m)
{
	char*** tab=malloc(sizeof(char**)*n);
	if(!tab)
	{
		return NULL;
	}
	unsigned i=0;
	for(;i<n;i++)
	{
		tab[i]=malloc(sizeof(char*)*m);
		if(!tab[i])
		{
			return NULL;
		}
		unsigned j=0;
		for(;j<m;j++)
		{
			tab[i][j]=malloc(sizeof(char)*8);
			if(!tab[i][j])
			{
				return NULL;
			}
		}
	}
	Grille* grille=malloc(sizeof(Grille));
	grille->m=m;
	grille->n=n;
	grille->tab=tab;
	grille->C1=0;
	grille->C2=0;
	return grille;
}
/*met toute les cases en noir
 */
void Grille_vider(Grille* g)
{
	unsigned i,j;
	for(i=0;i<g->n;i++)
	{
		for(j=0;j<g->m;j++)
		{
			str_e8(g->tab[i][j],"\33[00m  ");

		}
		if(i==g->n-1)
		{
			for(j=0;j<g->m;j++)
			{
				str_e8(g->tab[i][j],"\33[00m__");
			}
		}
	}
}
/*pose un fruit au hazar
 */
void Grille_tirage_fruit(Grille* g,Serpent* se)
{
	unsigned l=l_total(se);	
	srand(time(NULL));
	unsigned position=rand()%(g->n*g->m-l);
	unsigned pf=0;
	while(position)
	{
		pf++;
		if(g->tab[pf/g->m][pf%g->m][2]=='0'
				&& g->tab[pf/g->m][pf%g->m][3]=='0')
		{
			position--;
		}
	}
	g->C1=pf/g->m;
	g->C2=pf%g->m;
}

/*colore les cases de la grille
 */
void Grille_remplir(Grille* g,Serpent* se)
{
	/*pose le fruit
	 */
	if(g->C1==g->n-1)
	{
		str_c2(g->tab[g->C1][g->C2],41);
	}
	else
	{
		str_c2(g->tab[g->C1][g->C2],41);
	}
	/*pose le serpent
	 */
	unsigned i=0;
	for(;i<se->fin->taille;i++)
	{
		str_c2(g->tab[se->x+i][se->y],43);
	}
}
/*desalloue la grille
 */
void Grille_desallouer(Grille* g)
{
	unsigned int i=0;
	for(;i<g->n;i++)
	{
		unsigned int j=0;
		for(;j<g->m;j++)
		{
			if(g->tab[i][j])
				free(g->tab[i][j]);
		}
		free(g->tab[i]);
	}
	free(g->tab);
	free(g);
}
/*dessine la grille
 */
void Grille_redessiner(Grille* g)
{
	printf("\33[2J");
	unsigned int i,j;
	printf(" ");
	for(i=0;i<g->n;i++)
		printf("__");
	printf("\n");
	for(i=0;i<g->n;i++)
	{
		printf("|");
		for(j=0;j<g->m;j++)
		{
			printf("%s",g->tab[i][j]);
		}
		printf("\33[00m|");
		printf("\n");
	}
	printf("\n");
}

/*change deux string de taille 8
 */
void str_e8(char* b,const char* s)
{
	int i=0;
	for(;i<7;i++)
	{
		b[i]=s[i];
	}
	b[7]=0;
}
/*change de couleur
 */
void str_c2(char* b,const unsigned n)
{
	b[2]='0'+n/10%10;
	b[3]='0'+n%10;
}
/*compare deux tring
 */
int str_cmp(char* c2,char* c1)
{
	size_t i=0;
	while(c2[i] && c1[i] && c1[i]==c2[i])
	{
		i++;
	}
	return c2[i]==c1[i];
}
/*fonction puissance
 */
int power(int n,int p)
{
	int nn=n;
	while(p)
	{
		n=n*nn;
		p--;
	}
	return n;
}
