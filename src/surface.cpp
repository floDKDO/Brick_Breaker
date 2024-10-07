#include "surface.hpp"

//Classe qui encapsule SDL_Surface
Surface::Surface(TTF_Font* police, std::string texte, SDL_Color couleur)
{
    NCHK(this->surface = TTF_RenderText_Solid(police, texte.c_str(), couleur), TTF_GetError());
}

Surface::~Surface()
{
    if(this->surface != nullptr)
    {
        SDL_FreeSurface(this->surface);
        this->surface = nullptr;
    }
}


SDL_Surface* const& Surface::get_surface() const
{
    return this->surface;
}
