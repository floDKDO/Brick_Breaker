#include "renderer.hpp"

//Classe qui encapsule SDL_Renderer
Renderer::Renderer(SDL_Window* fenetre, const int index, const Uint32 flags)
:fenetre(fenetre), index(index), flags(flags)
{
    if((this->rendu = SDL_CreateRenderer(fenetre, index, flags)) == nullptr)
    {
        std::cerr << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
}

Renderer::~Renderer()
{
    if(this->rendu != nullptr)
    {
        SDL_DestroyRenderer(this->rendu);
        this->rendu = nullptr;
    }
}


SDL_Renderer* const& Renderer::get_renderer() const
{
    return this->rendu;
}
