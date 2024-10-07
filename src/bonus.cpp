#include "bonus.hpp"

Bonus::Bonus(const int x, const int y, std::mt19937& e, const SingletonSysteme* const sing_syst)
{
    this->position = {x, y, 42, 42};
    std::uniform_int_distribution<int> valeur{0, 100};
    int nombre = valeur(e);

    //une chance sur 3 d'avoir chacun des bonus
    if(nombre < 33)
    {
        this->sorte_bonus = MULTI_BALLES;
        this->texture = std::make_unique<Texture>(sing_syst->renderer->get_renderer(),  "./img/bonus_multi_balles.png");
    }
    else if(nombre >= 33 && nombre < 66)
    {
        this->sorte_bonus = GRANDE_BALLE;
        this->texture = std::make_unique<Texture>(sing_syst->renderer->get_renderer(),  "./img/bonus_grande_balle.png");
    }
    else
    {
        this->sorte_bonus = GRANDE_PLATEFORME;
        this->texture = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), "./img/bonus_grande_plateforme.png");
    }
}


void Bonus::draw(SDL_Renderer* const rendu) const
{
    CHK(SDL_RenderCopy(rendu, this->texture->get_texture(), nullptr, &this->position), SDL_GetError());
}


void Bonus::update()
{
    this->position.y += SPEED_OBJET;
}
