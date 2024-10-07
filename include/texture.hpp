#ifndef __TEXTURE__HPP__
#define __TEXTURE__HPP__

#include "singleton_systeme.hpp"

//Classe qui encapsule SDL_Texture
class Texture
{
    public:
        Texture(SDL_Renderer* const rendu, std::string chemin); //IMG_LoadTexture
        Texture(SDL_Renderer* const rendu, SDL_Surface* surface); //SDL_CreateTextureFromSurface
        ~Texture();
        SDL_Texture* const& get_texture() const;

    protected:

    private:
        SDL_Texture* texture;
};

#endif // __TEXTURE__HPP__
