#include "texte.hpp"

Texte::Texte(const std::string texte, const std::string police, const int taille_police, const SDL_Color couleur, const SDL_Rect position, SDL_Renderer* const rendu)
:position(position),
texte(texte),
couleur(couleur),
taille_police(taille_police)
{
    (void)rendu;
    NCHK(this->police = TTF_OpenFont(police.c_str(), taille_police), TTF_GetError());
    this->surface = std::make_unique<Surface>(this->police, this->texte.c_str(), couleur);

    this->position.w = surface->get_surface()->w;
    this->position.h = surface->get_surface()->h;
    this->texture = std::make_unique<Texture>(rendu, surface->get_surface());
}


void Texte::draw(SDL_Renderer* const rendu)
{
    position.w = surface->get_surface()->w;
    position.h = surface->get_surface()->h;
    CHK(SDL_RenderCopy(rendu, texture->get_texture(), nullptr, &position), SDL_GetError());
}

//modifier le texte
void Texte::edit_text(const std::string nouveau_texte, SDL_Renderer* const rendu)
{
    if(this->texte.length() > 0)
    {
        this->surface = std::make_unique<Surface>(this->police, nouveau_texte.c_str(), couleur);
    }
    else this->surface = std::make_unique<Surface>(this->police, " ", couleur);
    position.w = this->surface->get_surface()->w;
    position.h = this->surface->get_surface()->h;
    this->texture = std::make_unique<Texture>(rendu, surface->get_surface());
}

std::string Texte::int_to_string(const int value) const
{
    std::ostringstream chaine;
    chaine << value;
    return chaine.str();
}
