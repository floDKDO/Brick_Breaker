#include "selectionnable.hpp"

//Classe abstraite pour Bouton et Toggle
bool Selectionnable::verrou = true;


void Selectionnable::handle_events(SDL_Event e, SingletonSysteme* const sing_syst)
{
    int x, y; //position x et y de la souris
    SDL_GetMouseState(&x, &y);

    if(e.type == SDL_KEYDOWN)
    {
        this->on_key_pressed(e, sing_syst);
    }
    else if(e.type == SDL_KEYUP)
    {
        this->on_key_released(e, sing_syst);
    }
    else if(e.type == SDL_MOUSEMOTION)
    {
        if(collision(this->position, x, y) == true)
        {
            this->on_pointer_enter(e, sing_syst);
        }
        else
        {
            this->on_pointer_exit(e, sing_syst);
        }
    }
    else if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        if(e.button.button == SDL_BUTTON_LEFT)
        {
            this->on_pointer_down(e, sing_syst);
        }
    }
    else if(e.type == SDL_MOUSEBUTTONUP)
    {
        if(e.button.button == SDL_BUTTON_LEFT)
        {
            this->on_click(e, sing_syst);
        }
    }
}


bool Selectionnable::collision(SDL_Rect dest, int x, int y) const
{
    if(dest.y + dest.h > y
    && dest.y < y
    && dest.x + dest.w > x
    && dest.x < x)
    {
        return true;
    }
    else return false;
}


void Selectionnable::set_selected(Selectionnable* ui)
{
    if(ui != nullptr)
        ui->etat = SELECTED;
}

void Selectionnable::set_unselected(Selectionnable* previous)
{
    if(previous != nullptr)
        previous->etat = NORMAL;
}


void Selectionnable::on_pointer_enter(SDL_Event e, SingletonSysteme* const sing_syst)
{
    (void)e;
    if(son_joue == false && sing_syst->son_active == true && previous_etat != SELECTED) //previous pour eviter qu'un son se rejoue si on est dejà sur le bouton avec la souris et qu'on la bouge dessus
    {
        CHK(Mix_PlayChannel(1, hover_sound, 0), Mix_GetError());
        son_joue = true;
    }
    this->etat = SELECTED;
    this->previous_etat = etat;
}

void Selectionnable::on_pointer_exit(SDL_Event e, SingletonSysteme* const sing_syst)
{
    (void)sing_syst;
    (void)e;
    previous_etat = etat;
    son_joue = false;
}

void Selectionnable::on_pointer_down(SDL_Event e, SingletonSysteme* const sing_syst)
{
    (void)e;
    (void)sing_syst;
    int x, y; //position x et y de la souris
    SDL_GetMouseState(&x, &y);
    if(collision(this->position, x, y) == true)
    {
        this->etat = CLICKED;
        clic_avant_collision = false; //protection
    }
    else
    {
        clic_avant_collision = true; //protection
    }
}

void Selectionnable::set_selected_if_move(Selectionnable* select_on_up, Selectionnable* select_on_down, Selectionnable* select_on_left, Selectionnable* select_on_right)
{
    this->select_on_up = select_on_up;
    this->select_on_down = select_on_down;
    this->select_on_left = select_on_left;
    this->select_on_right = select_on_right;
}

void Selectionnable::on_key_released(SDL_Event e, SingletonSysteme* const sing_syst)
{
    (void)e;
    (void)sing_syst;
    this->verrou = true;
}


void Selectionnable::select_new(Selectionnable* ui, SingletonSysteme* const sing_syst)
{
    this->set_unselected(this);
    this->set_selected(ui);
    if(sing_syst->son_active == true && etat != SELECTED)
    {
        CHK(Mix_PlayChannel(1, hover_sound, 0), Mix_GetError());
        son_joue = true;
    }
}
