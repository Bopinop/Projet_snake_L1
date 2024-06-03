#include "interface.h"

// variable declarations
static Uint8 *audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play

// Updates the display.
//
// renderer: Renderer to draw on.
// texture: Texture that contains the image.
void draw(SDL_Renderer* renderer, SDL_Texture* texture)
{
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

// Event loop that calls the relevant event handler.
//
// renderer: Renderer to draw on.
// colored: Texture that contains the colored image.
// grayscale: Texture that contains the grayscale image.
void event_loop(SDL_Renderer* renderer, SDL_Texture* tex, SDL_Surface* surface,Grille* g,Serpent* se,
		char bouboul)
{
	SDL_Event event; // evenement possible
	clock_t tim =clock(); // temp global
	clock_t tim2 =clock(); // temp pour eater egg
	draw(renderer,tex); 
	char dir=0; // direction en question 0 est null
	double vitesse=0.5; // la vitesse du sepent case en seconde
	unsigned color =2112; // la couleur 
	char fruit=0; // stack de valeur de fruit
	int cmp_f=0; // compteur de nombre de fruit
	Uint8* wav_buffer=malloc(1); // buffer
	while (1)
	{
		//SDL_WaitEvent(&event);
		SDL_PollEvent(&event);

		switch (event.type)
		{
			// If the "quit" button is pushed, ends the event loop.
			case SDL_QUIT:
				return;

				// If the window is resized, updates and redraws the diagonals.
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					draw(renderer, tex);
				}
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym==SDLK_m)
				{
					vitesse+=0.1;
				}
				if(event.key.keysym.sym==SDLK_p)
				{
					if(vitesse>0.1)
					{
						vitesse-=0.1;
					}
				}
				if(event.key.keysym.sym==SDLK_LEFT)
				{
					if(se->fin->direction%2==1)
					{
						dir=4;
					}
				}
				if(event.key.keysym.sym==SDLK_RIGHT)
				{
					if(se->fin->direction%2==1)
					{
						dir=2;
					}

				}
				if(event.key.keysym.sym==SDLK_UP)
				{
					if(se->fin->direction%2==0)
					{
						dir=1;
					}

				}
				if(event.key.keysym.sym==SDLK_DOWN)
				{
					if(se->fin->direction%2==0)
					{
						dir=3;
					}
				}
		}
		// change la couleur
		color=(color*10)%1000000000+(color*10/1000000000);
		// si star est selectionner
		if(bouboul%10 &&(double)(clock()-tim)/CLOCKS_PER_SEC>0.001)
		{
			Set_map(surface,color);

		}
		// si ee est selectionner
		if(bouboul&10 && cmp_f>1)
		{
			add_squarre(surface,g->C2,g->C1,color);
			if((double)(clock()-tim2)/CLOCKS_PER_SEC>4)
			{
				if(bouboul&100)
				{

					SDL_CloseAudio();
					SDL_FreeWAV(wav_buffer);
				}
				wav_buffer=audio();
				tim2=clock();
				bouboul|=100;
			}
		}
		//bouge le serpent et dessine
		if((double)(clock()-tim)/CLOCKS_PER_SEC>vitesse)
		{
			tim=clock();
			if(dir)
			{
				Section* s= Allouer_Section(0,se->debut->couleur,dir);
				ajouter_section_fin(se,s);
			}
			dir=0;
			// bouge le serpent si il y a un problème il arrete le 
			// programme
			if(move_Snake(g,se,surface,&fruit,&cmp_f))
			{
				return;
			}
			tex= SDL_CreateTextureFromSurface(renderer,surface);
			draw(renderer,tex);
			if(g->n<=30 && g->m<=30)
			{
				Grille_redessiner(g);
			}

		}
	}
}
/*change la couleur pour faire croire que le serpent bouge
 * mouhahahaha
 */
int move_Snake(Grille* g, Serpent* se, SDL_Surface* surface,char* fruit,int* cmp_f)
{
	// modifie la taille puis les coordonne de la tete
	se->fin->taille+=1;
	if(se->fin->direction%2==0)
	{
		se->x-= (int)(se->fin->direction)-3;
	}
	else
	{
		se->y+= (int)(se->fin->direction)-2;
	}
	// si il n'est pas sur un fruit qu il n a plus de stack de fruit et que
	// sa tete passe par la case qui supprime
	// trivial quoi 
	if(!((se->x==g->C2 && se->y==g->C1)||*fruit)
			|| (se->x==se->x_f&&se->y==se->y_f))
	{
		//bouge la case de suppresion
		se->debut->taille-=1;
		if (se->debut->taille==0)
		{
			Section* s=retire_section_debut(se);
			Desallouer_Section(s);
			if(s->direction%2==0)
			{
				se->x_f-=(int)(s->direction)-3;
			}
			else
			{
				se->y_f+=(int)(s->direction)-2;
			}
		}
		else{
			if(se->debut->direction%2==0)
			{
				se->x_f-=(int)(se->debut->direction)-3;
			}
			else
			{
				se->y_f+=(int)(se->debut->direction)-2;
			}
		}
	}
	else
	{
		// pour repose un nouveaux fruit
		if((se->x==g->C2 && se->y==g->C1))
		{
			*cmp_f+=1;
			srand(time(NULL));
			*fruit+=rand()%4+1;
			Grille_tirage_fruit(g,se);
			add_squarre(surface,g->C2,g->C1,255000000);
			str_c2(g->tab[g->C1][g->C2],41);
		}
		*fruit-=1;
	}
	// si il se mort ou vas a l'exterieur
	if(se->x>g->m-1 || se->y>g->n-1 || 
			(g->tab[se->y][se->x][2]=='4' 
			 && g->tab[se->y][se->x][3]=='3')
	  )
		return 1;
	add_squarre(surface,se->x,se->y,se->debut->couleur);
	// colorie en noir et efface
	if((!(se->x_f==g->C2 && se->y_f==g->C1))&&*fruit==0)	
	{
		add_squarre(surface,se->x_f,se->y_f,0);
		str_c2(g->tab[se->y_f][se->x_f],0);
	}
	str_c2(g->tab[se->y][se->x],43);
	return 0;
}

Uint32 copy_pixel(Uint32 pixel,SDL_PixelFormat* format)
	//deep copy of pixel
{

	Uint8 r, g, b;
	SDL_GetRGB(pixel, format, &r, &g, &b);
	return SDL_MapRGB(format, r,g ,b );
}

SDL_Surface* C_Surface(int w,int h)
{
	SDL_Surface* surface = NULL;

	//La transparence n'est pas activée
	surface = SDL_CreateRGBSurface (0, w, h, 32, 0, 0, 0, 0);

	if(surface == NULL)
	{
		errx(EXIT_FAILURE, "%s", SDL_GetError());
	}
	return surface;
}
/*color squarre on surface
*/
void add_squarre(SDL_Surface* surface,unsigned w, unsigned h,unsigned color)
{
	SDL_LockSurface(surface);
	Uint32* pixels=surface->pixels;
	SDL_PixelFormat* format=surface->format;
	size_t position=((h*10)+10)*surface->w+w*10;
	size_t i=0;
	for(;i<10*10;i++)
	{
		pixels[position+i%10+(i/10*(surface->w))+10]=
			SDL_MapRGB(format, 
					color/1000000,
					color%1000000/1000 ,
					color%1000 );
	}
	SDL_UnlockSurface(surface);
}
/*color all sides of surface
*/
void Set_map(SDL_Surface* surface,unsigned color)
{
	SDL_LockSurface(surface);
	Uint32* pixels=surface->pixels;
	SDL_PixelFormat* format=surface->format;
	int i=0;
	for(;i<surface->h*surface->w;i++)
	{
		if(i/surface->w<10 || i%surface->w>=surface->w-10 
				|| i%surface->w<10
				||i/surface->w>=surface->h-10)
		{
			pixels[i]=
				SDL_MapRGB(format,
						color/1000000,
						color%1000000/1000 ,
						color%1000 );
		}
	}
	SDL_UnlockSurface(surface);
}

void Create_picture(Grille* g, Serpent *se,char bouboul)
{
	// - Create a window.
	SDL_Window* window = 
		SDL_CreateWindow("My picture", 0, 0, 640, 640,
				SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == NULL)
		errx(EXIT_FAILURE, "%s", SDL_GetError());

	// - Create a renderer.
	SDL_Renderer* renderer = 
		SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
		errx(EXIT_FAILURE, "%s", SDL_GetError());

	// - Create a surface from the colored image.
	//SDL_Surface* surface= load_image(argv[1]); 
	// - Resize the window according to the size of the image.
	//SDL_SetWindowSize(renderer, surface->w,surface->h);
	SDL_Surface* surface= C_Surface(20+g->m*10,20+g->n*10);

	// - Create a texture from the colored surface.
	Set_map(surface,255);
	add_squarre(surface,g->C2,g->C1,255000000);
	SDL_Texture* texture= SDL_CreateTextureFromSurface(renderer,surface);

	//surface_to_image_ave(surface); 
	// - Create a new texture from the grayscale surface.
	//SDL_Texture* textureg= SDL_CreateTextureFromSurface(renderer,surface);

	// - Dispatch the events.
	event_loop(renderer, texture,surface,g,se,bouboul);

	// - Free the surface.
	SDL_FreeSurface( surface);


	// - Destroy the objects.
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}


Uint8* audio()
{
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		return NULL;

	static Uint32 wav_length; 
	static Uint8 *wav_buffer;
	static SDL_AudioSpec wav_spec;


	/* Load the WAV */
	if( SDL_LoadWAV("boume.wav", &wav_spec, &wav_buffer, &wav_length) == NULL ){
		return NULL;
	}

	wav_spec.callback = my_audio_callback;
	wav_spec.userdata = NULL;

	audio_pos = wav_buffer; // copy sound buffer
	audio_len = wav_length; // copy file length


	if ( SDL_OpenAudio(&wav_spec, NULL) < 0 ){
		fprintf(stderr, "on ne peut ouvrir l'audio: %s\n", SDL_GetError());
		exit(-1);
	}

	SDL_PauseAudio(0);

	return wav_buffer;

}

void my_audio_callback(void *userdata, Uint8 *stream, int len) {

	if (audio_len ==0)
		return;

	len = ( (unsigned)len > audio_len ? audio_len : (unsigned)len );
	userdata+=1;
	SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

	audio_pos += len;
	audio_len -= len;
}

void selection_for_main(int argc, char** argv,
		unsigned* n, unsigned* m, unsigned* c, char* bouboul)
{

	int i=1;
	for(;i<argc;i++)
	{
		if(str_cmp(argv[i],"-size"))
		{
			if(i+2<argc)
			{
				int j=0;
				*n=0;
				*m=0;
				i++;
				for(;argv[i][j];j++)
				{
					if(argv[i][j]>='0' && argv[i][j]<='9')
						*n=*n*10+argv[i][j]-'0';
				}
				j=0;
				i++;
				for(;argv[i][j];j++)
				{
					if(argv[i][j]>='0' && argv[i][j]<='9')
						*m=*m*10+argv[i][j]-'0';
				}
				if(*n<10 || *m<10)
				{
					*n=10;
					*m=10;
				}
			}
		}
		if(str_cmp(argv[i],"-color"))
		{
			if(i+3<argc)
			{	
				int j=0;
				*c=0;
				i++;
				for(;argv[i][j];j++)
				{
					if(argv[i][j]>='0' && argv[i][j]<='9')
						*c=*c*10+argv[i][j]-'0';
				}
				j=0;
				i++;
				for(;argv[i][j];j++)
				{
					if(argv[i][j]>='0' && argv[i][j]<='9')
						*c=*c*10+argv[i][j]-'0';
				}
				if(j<3)
				{
					*c=(*c/(power(10,j-1)))
						*(power(10,3-j))
						+*c%(power(10,j-1));
				}
				j=0;
				i++;
				for(;argv[i][j];j++)
				{
					if(argv[i][j]>='0' && argv[i][j]<='9')
						*c=*c*10+argv[i][j]-'0';
				}
				if(j<3)
				{
					*c=(*c/(power(10,j-1)))
						*(power(10,3-j))+
						*c%(power(10,j-1));
				}
			}
		}
		if(str_cmp(argv[i],"-star"))
		{
			*bouboul=*bouboul|1;
		}
		if(str_cmp(argv[i],"-ee"))
		{
			*bouboul=*bouboul|10;
		}
	}
}
