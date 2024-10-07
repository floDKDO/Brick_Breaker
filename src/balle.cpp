#include "balle.hpp"

//Constructeur pour les balles générées par le bonus MULTI_BALLES
Balle::Balle(int x, int y, SingletonSysteme* const sing_syst)
:position{x, y, this->TAILLE_NORMALE, this->TAILLE_NORMALE},
velocity_y(-SPEED), //la balle monte toujours
chemin("./img/balle.png")
{
    std::array<float, 5> tab_random_velocity_x = {-1, -0.5, 0, 0.5, 1};
    std::uniform_int_distribution<int> random_indice{0, 4}; //indice dans le tableau tab_random_velocity_xX pour déterminer une velocityX aléatoire
    float random_velocity_x = tab_random_velocity_x[random_indice(sing_syst->e)] * SPEED;
    this->velocity_x = random_velocity_x;

    this->texture = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), this->chemin.c_str());
}

//Constructeur pour la balle générée au début d'un niveau
Balle::Balle(SingletonSysteme* const sing_syst)
:position{500, 380, this->TAILLE_NORMALE, this->TAILLE_NORMALE},
velocity_y(SPEED), //la balle monte toujours
chemin("./img/balle.png")
{
    std::array<float, 5> tab_random_velocity_x = {-1, -0.5, 0, 0.5, 1};
    std::uniform_int_distribution<int> random_indice{0, 4}; //indice dans le tableau tab_random_velocity_x pour déterminer une velocityX aléatoire
    float random_velocity_x = tab_random_velocity_x[random_indice(sing_syst->e)] * SPEED;
    this->velocity_x = random_velocity_x;

    this->texture = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), this->chemin.c_str());
}

bool Balle::is_big()
{
    int grande_taille = this->TAILLE_NORMALE + 10;
    return this->position.w == grande_taille && this->position.h == grande_taille;
}

bool Balle::is_small()
{
    int petite_taille = this->TAILLE_NORMALE - 10;
    return this->position.w == petite_taille && this->position.h == petite_taille;
}

void Balle::set_size_big()
{
    int grande_taille = this->TAILLE_NORMALE + 10;
    this->position.w = grande_taille;
    this->position.h = grande_taille;
}

void Balle::set_size_small()
{
    int petite_taille = this->TAILLE_NORMALE - 10;
    this->position.w = petite_taille;
    this->position.h = petite_taille;
}

void Balle::set_size_normal()
{
    this->position.w = this->TAILLE_NORMALE;
    this->position.h = this->TAILLE_NORMALE;
}

void Balle::draw(SDL_Renderer* const rendu) const
{
    CHK(SDL_RenderCopy(rendu, this->texture->get_texture(), nullptr, &this->position), SDL_GetError());
}

void Balle::update()
{
    this->position.x += this->velocity_x;
    this->position.y += this->velocity_y;
}
