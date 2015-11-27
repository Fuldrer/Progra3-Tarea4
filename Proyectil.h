#ifndef PROJECTIL_H
#define PROJECTIL_H
#include <SDL_ttf.h>

#include <list>
#include "Entidad.h"
#include "Enemigo.h"

using namespace std;

class Proyectil : public Entidad
{
    public:
        SDL_Renderer* renderer;
        list<Entidad*>* entidades;
        SDL_Texture* texture;
        SDL_Rect rect;
        int *contador;
        string state;
        Proyectil(list<Entidad*>* entidades,SDL_Renderer* renderer, int x, int y, string state, int *contador);
        virtual ~Proyectil();
        void dibujar();
        void logica();
    protected:
    private:
};

#endif // PROJECTIL_H
