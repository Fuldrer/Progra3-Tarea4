#ifndef JUGADOR_H
#define JUGADOR_H

#include <list>
#include <SDL_mixer.h>
#include <stdio.h>
#include "Personaje.h"
#include "Proyectil.h"

class Jugador : public Personaje
{
    public:
        int vidas;
        int proyectil_cooldown;
        int *contador;
        Jugador(list<Entidad*>* entidades,SDL_Renderer* renderer, int *contador);
        virtual ~Jugador();
        void logica();
        void logicaPush();
        void dibujar();
    protected:
    private:
};

#endif // JUGADOR_H
