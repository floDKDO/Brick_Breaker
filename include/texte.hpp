#ifndef __TEXTE__HPP__
#define __TEXTE__HPP__

#include "singleton_systeme.hpp"
#include <memory>
#include <sstream>

class Texte
{
    public:
        Texte(const std::string texte, const std::string police, const int taille_police, const SDL_Color couleur, const SDL_Rect position, SDL_Renderer* const rendu);

        void draw(SDL_Renderer* const rendu);
        std::string int_to_string(const int value) const;
        void edit_text(const std::string nouveau_texte, SDL_Renderer* const rendu);

    protected:

    private:
        SDL_Rect position;
        std::string texte;
        TTF_Font* police;
        SDL_Color couleur;
        std::unique_ptr<Surface> surface;
        std::unique_ptr<Texture> texture;
        int taille_police;
};

#endif // __TEXTE__HPP__
