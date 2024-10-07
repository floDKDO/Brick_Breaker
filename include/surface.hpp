#ifndef __SURFACE__HPP__
#define __SURFACE__HPP__

#include "singleton_systeme.hpp"

//Classe qui encapsule SDL_Surface
class Surface
{
    public:
        Surface(TTF_Font* police, std::string texte, SDL_Color couleur); //TTF_RenderText_Solid
        ~Surface();
        SDL_Surface* const& get_surface() const;

    protected:

    private:
        SDL_Surface* surface;

};

#endif // __SURFACE__HPP__
