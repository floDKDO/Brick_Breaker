#include "texture.hpp"

//Classe qui encapsule SDL_Texture
Texture::Texture(SDL_Renderer* const rendu, std::string chemin) //IMG_LoadTexture
{
    NCHK(this->texture = IMG_LoadTexture(rendu, chemin.c_str()), IMG_GetError());
}


Texture::Texture(SDL_Renderer* const rendu, SDL_Surface* surface) //SDL_CreateTextureFromSurface
{
    NCHK(this->texture = SDL_CreateTextureFromSurface(rendu, surface), SDL_GetError());
}


Texture::~Texture()
{
    if(this->texture != nullptr)
    {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }
}

SDL_Texture* const& Texture::get_texture() const
{
    return this->texture;
}

