#ifndef __RENDERER__HPP__
#define __RENDERER__HPP__

#include <SDL2/SDL.h>
#include <iostream>

//Classe qui encapsule SDL_Renderer
class Renderer
{
    public:
        Renderer(SDL_Window* fenetre, const int index, const Uint32 flags);
        ~Renderer();
        SDL_Renderer* const& get_renderer() const;

    protected:

    private:
        SDL_Renderer* rendu;
        SDL_Window* fenetre;
        int index;
        Uint32 flags;
};

#endif
