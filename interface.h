#ifndef INTERFACE_H /* garde d'inclusion */
#define INTERFACE_H
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <pthread.h>
#include<time.h>
#include "grille.h"


void draw(SDL_Renderer* renderer, SDL_Texture* texture);
void event_loop(SDL_Renderer* renderer, SDL_Texture* tex, SDL_Surface* surface,Grille* g,Serpent*,char);
Uint32 copy_pixel(Uint32 pixel,SDL_PixelFormat* format);
SDL_Surface* C_Surface(int w,int h);
void Create_picture(Grille*,Serpent*,char);
void add_squarre(SDL_Surface* surface,unsigned w, unsigned h,unsigned color);
int move_Snake(Grille* g, Serpent* se, SDL_Surface* surface,char*,int*);
void Set_map(SDL_Surface* surface,unsigned color);
Uint8* audio(); 
void selection_for_main(int argc, char** argv,
		unsigned* n, unsigned* m, unsigned* c, char* bouboul);
void my_audio_callback(void *userdata, Uint8 *stream, int len);
#endif
