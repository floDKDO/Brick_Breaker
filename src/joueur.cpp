#include "joueur.hpp"

Joueur::Joueur(const SingletonSysteme* const sing_syst)
:position{sing_syst->LONGUEUR_FENETRE/2 - 100/2, 640, 100, 30},
taille_plateforme(NORMALE),
angle(0.0f)
{
    for(int i = 0; i < 2; i++)
    {
        this->dep[i] = false;
    }

    if(sing_syst->type_deplacement == CLASSIQUE)
    {
        this->position = {sing_syst->LONGUEUR_FENETRE/2 - 100/2, 640, 100, 30};
        this->texture[0] = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), "./img/plateforme_normale.png");
    }
    else //retourner la plateforme
    {
        this->position = {sing_syst->LONGUEUR_FENETRE/2 - 100/2, 640, 30, 100};
        this->texture[0] = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), "./img/plateforme_normale_rotation.png");
    }

    this->texture[1] = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), "./img/petite_plateforme.png");
    this->texture[2] = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), "./img/grande_plateforme.png");
}

void Joueur::reset_all_values()
{
    for(int i = 0; i < 2; i++)
    {
        dep[i] = false;
    }
}

void Joueur::set_size_big()
{
    this->position.w += 30;
    this->taille_plateforme = GRANDE;
    this->position.x -= 30/2;
}

void Joueur::set_size_small()
{
    this->position.w -= 30;
    this->position.x += 30/2;
    this->taille_plateforme = PETITE;
}

void Joueur::set_size_normal()
{
    if(this->taille_plateforme == GRANDE)
    {
        this->position.w -= 30;
        this->position.x += 30/2;
    }
    else if(this->taille_plateforme == PETITE)
    {
        this->position.w += 30;
        this->position.x -= 30/2;
    }
    this->taille_plateforme = NORMALE;
}


void Joueur::reset_position(SingletonSysteme* sing_syst)
{
    this->position = {sing_syst->LONGUEUR_FENETRE/2 - 100/2, 660, 100, 30};
}

//pour les déplacements gauche ou droite avec le clavier
void Joueur::set_value(const int indice)
{
    reset_all_values();
    dep[indice] = true;
}

void Joueur::draw(SDL_Renderer* const rendu) const
{
    SDL_Rect temp = {position.x, position.y, position.w, position.h};

    if(this->taille_plateforme == NORMALE)
    {
        CHK(SDL_RenderCopyEx(rendu, this->texture[0]->get_texture(), nullptr, &temp, angle * 180.0 / M_PI, nullptr, SDL_FLIP_NONE), SDL_GetError());
    }
    else if(this->taille_plateforme == PETITE)
    {
        CHK(SDL_RenderCopyEx(rendu, this->texture[1]->get_texture(), nullptr, &temp, angle * 180.0 / M_PI, nullptr, SDL_FLIP_NONE), SDL_GetError());
    }
    else if(this->taille_plateforme == GRANDE)
    {
        CHK(SDL_RenderCopyEx(rendu, this->texture[2]->get_texture(), nullptr, &temp, angle * 180.0 / M_PI, nullptr, SDL_FLIP_NONE), SDL_GetError());
    }
}

void Joueur::handle_events(const SDL_Event e, const SingletonSysteme* const sing_syst)
{
    int x, y; //position x et y de la souris
    SDL_GetMouseState(&x, &y);

    if(sing_syst->type_deplacement == CLASSIQUE)
    {
        if(sing_syst->mode_deplacement == CLAVIER)
        {
            if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_LEFT)
                {
                    set_value(0);
                }
                else if(e.key.keysym.sym == SDLK_RIGHT)
                {
                    set_value(1);
                }
            }
            else if(e.type == SDL_KEYUP)
            {
                reset_all_values();
            }
        }
        else if(sing_syst->mode_deplacement == SOURIS)
        {
            if(e.type == SDL_MOUSEMOTION)
            {
                this->position.x = x;

                //pour ne pas que le joueur sorte de la zone
                int offset_x_zone = 189; //décalage de la zone par rapport à la coordonnée x de l'écran
                int offset_zone = 25; //largeur en x de la zone

                //le joueur ne doit pas sortir de la zone = carré entourant la zone de jeu
                if(this->position.x <= offset_x_zone + offset_zone) //gauche de la zone
                {
                    this->position.x = offset_x_zone + offset_zone;
                }
                else if(this->position.x + this->position.w >= sing_syst->LONGUEUR_FENETRE - offset_x_zone - offset_zone) //droite de la zone
                {
                    this->position.x = sing_syst->LONGUEUR_FENETRE - offset_x_zone - offset_zone - this->position.w;
                }
            }
        }
    }
    else if(sing_syst->type_deplacement == CIRCULAIRE) //marche qu'avec le clavier
    {
        if(e.type == SDL_KEYDOWN)
        {
            if(e.key.keysym.sym == SDLK_LEFT)
            {
                set_value(0);
            }
            else if(e.key.keysym.sym == SDLK_RIGHT)
            {
                set_value(1);
            }
        }
        else if(e.type == SDL_KEYUP)
        {
            reset_all_values();
        }
    }
}

void Joueur::update(const SingletonSysteme* const sing_syst)
{
    if(sing_syst->mode_deplacement == CLAVIER)
    {
        if(sing_syst->type_deplacement == CLASSIQUE)
        {
            if(this->dep[0] == true)
            {
                this->position.x -= this->VITESSE_DEPLACEMENT;
            }
            else if(this->dep[1] == true)
            {
                this->position.x += this->VITESSE_DEPLACEMENT;
            }
        }
    }

    if(sing_syst->type_deplacement == CIRCULAIRE)
    {
        const float circle_radius_player = 300.0f; //rayon sur lequel le joueur peut se déplacer en mode circulaire

        float delta_x = cos(angle) * circle_radius_player - cos(0) * circle_radius_player;
        float delta_y = sin(angle) * circle_radius_player - sin(0) * circle_radius_player;

        if(this->dep[0] == true)
        {
            angle += 0.1;
        }
        else if(this->dep[1] == true)
        {
            angle -= 0.1;
        }
        this->position.x += sing_syst->LONGUEUR_FENETRE / 2 - this->position.w / 2 + delta_x - this->position.x + circle_radius_player;
        this->position.y += sing_syst->HAUTEUR_FENETRE / 2 - this->position.h / 2 + delta_y - this->position.y;
    }
}
