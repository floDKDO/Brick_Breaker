#include "tuile.hpp"

//brique pour mode normal
Tuile::Tuile(const std::string chemin, const int x, const int y, const unsigned int point_de_vie, std::mt19937& e, const SingletonSysteme* const sing_syst) //brique classique
:point_de_vie(point_de_vie),
point_de_vie_actuel(point_de_vie),
une_fois(false)
{
    this->chemin = chemin;
    this->position = {x, y, 52, 52};

    if(this->point_de_vie == 1)
        this->nb_points = 50;
    else if(this->point_de_vie == 2)
        this->nb_points = 100;
    else if(this->point_de_vie == 3)
        this->nb_points = 200;

    std::uniform_int_distribution<int> valeur{0, 100}; //pour générer un bonus/malus
    this->random_value = valeur(e);

    this->texture = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), this->chemin.c_str());
}

//brique pour mode CIRCULAIRE
Tuile::Tuile(SDL_Color couleur, const int x, const int y)
:point_de_vie(1),
point_de_vie_actuel(1),
random_value(10),
texture(nullptr),
couleur(couleur),
une_fois(false)
{
    this->position = {x, y, 52, 52};

    if(this->point_de_vie == 1)
        this->nb_points = 50;
    else if(this->point_de_vie == 2)
        this->nb_points = 100;
    else if(this->point_de_vie == 3)
        this->nb_points = 200;
}


void Tuile::draw(SDL_Renderer* const rendu)
{
    if(this->texture != nullptr) //brique classique
    {
        CHK(SDL_RenderCopy(rendu, this->texture->get_texture(), nullptr, &this->position), SDL_GetError());
    }
    else //brique mode circulaire
    {
        CHK(SDL_SetRenderDrawColor(rendu, this->couleur.r, this->couleur.g, this->couleur.b, this->couleur.a), SDL_GetError());
        CHK(SDL_RenderFillRect(rendu, &this->position), SDL_GetError());
    }
}


void Tuile::update(const SingletonSysteme* const sing_syst)
{
    (void)sing_syst;

    if(this->point_de_vie == 3) //la brique a 3 pv et s'est fait touchée => elle possède maintenant 2 pv, faire ce code une seule fois
    {
        if(this->point_de_vie_actuel == 2 && this->une_fois == false)
        {
            this->chemin = "./img/brique_rouge_petite_fissure.png";
            this->texture = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), this->chemin.c_str());
            this->une_fois = true;
        }
        else if(this->point_de_vie_actuel == 1 && this->une_fois == true)
        {
            this->chemin = "./img/brique_rouge_grande_fissure.png";
            this->texture = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), this->chemin.c_str());
            this->une_fois = false;
        }
    }
    else if(this->point_de_vie == 2 && this->point_de_vie_actuel == 1 && this->une_fois == false) //la brique a 2 pv et s'est fait touchée => elle possède maintenant 1 pv, faire ce code une seule fois
    {
        this->chemin = "./img/brique_grise_fissure.png";
        this->texture = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), this->chemin.c_str());
        this->une_fois = true;
    }
}
