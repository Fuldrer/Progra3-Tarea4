#include "Proyectil.h"
#include <SDL_ttf.h>



Proyectil::Proyectil(list<Entidad*>* entidades, SDL_Renderer* renderer, int x, int y, string state, int *contador)
{
    this->contador = contador;
    tipo = "Proyectil";
    this->entidades = entidades;
    this->renderer = renderer;
    this->state = state;
    texture = IMG_LoadTexture(renderer,"proyectil.png");
    rect.x=x;
    rect.y=y;
    rect.w=20;
    rect.h=10;
}

Proyectil::~Proyectil()
{
    //dtor
}

void Proyectil::dibujar()
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Proyectil::logica()
{
    int puntos = 0;
    int velocity = 3;
    Mix_OpenAudio(22052,MIX_DEFAULT_FORMAT,2,4096);
    if(state=="right")
    {
        rect.x+=velocity;
    }
    if(state=="left")
    {
        rect.x-=velocity;
    }
    if(state=="up")
    {
        rect.y-=velocity;
    }
    if(state=="down")
    {
        rect.y+=velocity;
    }

    for(list<Entidad*>::iterator e=entidades->begin();
        e!=entidades->end();
        e++)
    {
        if((*e)->tipo=="Enemigo")
        {
            Enemigo* enemigo = (Enemigo*)(*e);
            if(colision(rect,enemigo->rect))
            {
                *contador+=2;
                Mix_Music *music = Mix_LoadMUS("Boom.wav");
                Mix_PlayMusic(music,1);
                Mix_CloseAudio();
                enemigo->delete_flag = true;
                this->delete_flag = true;
                cout<<puntos<<endl;
                cout<<"Colision con proyectil"<<endl;
            }
        }
    }

    if(rect.x<0 || rect.x>500 || rect.y<0 || rect.y>250)
    {
        this->delete_flag=true;
        cout<<"Borrando bala"<<endl;
    }
}





