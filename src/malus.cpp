#include "malus.hpp"

Malus::Malus(const int x, const int y, std::mt19937& e, const SingletonSysteme* const sing_syst)
{
    this->position = {x, y, 42, 42};
    std::uniform_int_distribution<int> valeur{0, 100};
    int nombre = valeur(e);

    //une chance sur deux d'avoir chacun des deux malus
    if(nombre < 50)
    {
        this->sorte_malus = PETITE_BALLE;
        this->texture = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), "./img/malus_petite_balle.png");
    }
    else
    {
        this->sorte_malus = PETITE_PLATEFORME;
        this->texture = std::make_unique<Texture>(sing_syst->renderer->get_renderer(),  "./img/malus_petite_plateforme.png");
    }
}


void Malus::draw(SDL_Renderer* const rendu) const
{
    CHK(SDL_RenderCopy(rendu, this->texture->get_texture(), nullptr, &this->position), SDL_GetError());
}


void Malus::update()
{
    this->position.y += SPEED_OBJET;
}
