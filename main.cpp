#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h> 	/* srand, rand */
#include <time.h>       /* time */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include<list>

#include "Jugador.h"
#include "Enemigo.h"
#include "Proyectil.h"
#include "Vida.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*character;
SDL_Rect rect_background,rect_character;
int con;
int*contador;
TTF_Font* font;
SDL_Color color;
SDL_Surface* surfacemessage;
SDL_Texture* message;
SDL_Rect messagerect;

using namespace std;

namespace temp
{
    template <typename T> std::string to_string(const T &n)
    {
        std::ostringstream stm;
        stm<<n;
        return stm.str();
    }
}

int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 1200/*WIDTH*/, 500/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    TTF_Init();
    font =TTF_OpenFont("sdone.ttf", 30);
    color = {255,255,255};
    surfacemessage = TTF_RenderText_Solid(font,temp::to_string(con).c_str(), color);
    message = SDL_CreateTextureFromSurface(renderer, surfacemessage);
    messagerect.x = 400;
    messagerect.y = 5;
    messagerect.h = 25;
    messagerect.w = 50;
    //Init textures
    con = 0;
    contador = &con;
    int w=0,h=0;

    background = IMG_LoadTexture(renderer,"esenario2.jpg");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = w;
    rect_background.h = h;

    character = IMG_LoadTexture(renderer, "personaje.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character.x = 0;
    rect_character.y = 100;
    rect_character.w = w;
    rect_character.h = h;

    SDL_Texture* otro_personaje = IMG_LoadTexture(renderer,"otropersonaje.png");
    SDL_Rect otro_rect;
    otro_rect.x=150;
    otro_rect.y=50;
    otro_rect.w=32;
    otro_rect.h=32;


    list<Entidad*>entidades;
    entidades.push_back(new Jugador(&entidades,renderer,contador));
    entidades.push_back(new Vida(&entidades,renderer));

    double last_frame=0;
    int frame=0;
    //Main Loop
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_d)
                    rect_character.x++;
            }
        }

        int spawn_frequency=60-(frame/100);
        if(spawn_frequency<5)
            spawn_frequency=5;
        if(frame%spawn_frequency==0)
            entidades.push_back(new Enemigo(&entidades,renderer));

        //SDL_Delay(17-(SDL_GetTicks()-last_frame));
        double diferencia = SDL_GetTicks()-last_frame;
        double ajuste = 17 - diferencia;
        if(ajuste>0)
            SDL_Delay(ajuste);
        last_frame=SDL_GetTicks();

        for(list<Entidad*>::iterator e = entidades.begin();
            e!=entidades.end();
            e++)
            (*e)->logica();

        for(list<Entidad*>::iterator e = entidades.begin();
            e!=entidades.end();
            e++)
        {
            if((*e)->delete_flag)
            {
                entidades.remove(*e);
                break;
            }
        }

        surfacemessage = TTF_RenderText_Solid(font,temp::to_string(con).c_str(), color);
        message = SDL_CreateTextureFromSurface(renderer, surfacemessage);

        SDL_RenderCopy(renderer, background, NULL, &rect_background);
        SDL_RenderCopy(renderer, message, NULL, &messagerect);



        for(int i=0;i<2;i++)
        {
            for(list<Entidad*>::iterator e = entidades.begin();
                e!=entidades.end();
                e++)
            {
                if((*e)->capa==i)
                    (*e)->dibujar();
            }
        }

        SDL_RenderPresent(renderer);
        frame++;
    }

	return 0;
}
