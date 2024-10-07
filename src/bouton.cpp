#include "bouton.hpp"

Bouton::Bouton(const std::string image_bouton, const std::string image_texte, const SDL_Rect position, eventFunction func_ptr, SDL_Renderer* const rendu)
{
    this->etat = NORMAL; //etat de base
    this->son_joue = false;
    this->clic_avant_collision = false; //protection
    this->previous_etat = etat;

    this->image_bouton = std::make_unique<Texture>(rendu, image_bouton.c_str());
    this->image_texte = std::make_unique<Texture>(rendu, image_texte.c_str());
    this->filtre_bouton_hovered = std::make_unique<Texture>(rendu, "./img/filtre_bouton_hovered.png");
    this->filtre_bouton_clicked = std::make_unique<Texture>(rendu, "./img/filtre_bouton_clicked.png");

    int w, h;
    CHK(SDL_QueryTexture(this->image_bouton->get_texture(), nullptr, nullptr, &w, &h), SDL_GetError());
    this->position = {position.x, position.y, w, h};
    this->func_ptr = func_ptr; //pointeur sur la fonction qui sera lancée quand il y aura un clic sur le bouton
    NCHK(this->hover_sound = Mix_LoadWAV("./sound/hover.wav"), Mix_GetError());
    NCHK(this->click_sound = Mix_LoadWAV("./sound/select.wav"), Mix_GetError());
}

Bouton::~Bouton()
{
    Mix_FreeChunk(this->hover_sound);
    Mix_FreeChunk(this->click_sound);
}


//collision entre la souris et le bouton
bool Bouton::collision(SDL_Rect dest, int x, int y) const
{
    return Selectionnable::collision(dest, x, y);
}

void Bouton::draw(SDL_Renderer* const rendu)
{
    CHK(SDL_RenderCopy(rendu, image_bouton->get_texture(), nullptr, &(this->position)), SDL_GetError());
    CHK(SDL_RenderCopy(rendu, image_texte->get_texture(), nullptr, &(this->position)), SDL_GetError());
    if(this->etat == HOVERED || this->etat == SELECTED)
    {
        CHK(SDL_RenderCopy(rendu, filtre_bouton_hovered->get_texture(), nullptr, &(this->position)), SDL_GetError());
    }
    else if(this->etat == CLICKED)
    {
        CHK(SDL_RenderCopy(rendu, this->filtre_bouton_clicked->get_texture(), nullptr, &(this->position)), SDL_GetError());
    }
}

void Bouton::handle_events(SDL_Event e, SingletonSysteme* const sing_syst)
{
    Selectionnable::handle_events(e, sing_syst);
}

void Bouton::on_key_pressed(SDL_Event e, SingletonSysteme* const sing_syst)
{
    if(this->etat == SELECTED && verrou == true)
    {
        if(e.key.keysym.sym == SDLK_UP)
        {
            if(this->select_on_up != nullptr)
            {
                this->select_new(this->select_on_up, sing_syst);
            }
        }
        else if(e.key.keysym.sym == SDLK_DOWN)
        {
            if(this->select_on_down != nullptr)
            {
                this->select_new(this->select_on_down, sing_syst);
            }
        }
        else if(e.key.keysym.sym == SDLK_LEFT)
        {
            if(this->select_on_left != nullptr)
            {
                this->select_new(this->select_on_left, sing_syst);
            }
        }
        else if(e.key.keysym.sym == SDLK_RIGHT)
        {
            if(this->select_on_right != nullptr)
            {
                this->select_new(this->select_on_right, sing_syst);
            }
        }

        if(e.key.keysym.sym == SDLK_RETURN)
        {
            if(this->etat == SELECTED)
            {
                if(sing_syst->son_active == true)
                {
                    CHK(Mix_PlayChannel(1, click_sound, 0), Mix_GetError());
                }
                this->func_ptr(sing_syst, this);
            }
        }
        else verrou = false;
    }
}


void Bouton::on_key_released(SDL_Event e, SingletonSysteme* const sing_syst)
{
    Selectionnable::on_key_released(e, sing_syst);
}

void Bouton::on_pointer_enter(SDL_Event e, SingletonSysteme* const sing_syst)
{
    Selectionnable::on_pointer_enter(e, sing_syst);
}


void Bouton::on_pointer_exit(SDL_Event e, SingletonSysteme* const sing_syst)
{
    Selectionnable::on_pointer_exit(e, sing_syst);
}

void Bouton::on_click(SDL_Event e, SingletonSysteme* const sing_syst)
{
    (void)e;
    int x, y; //position x et y de la souris
    SDL_GetMouseState(&x, &y);
    if(collision(this->position, x, y) == true && clic_avant_collision == false) //empecher de cliquer avant d'etre sur le bouton
    {
        this->etat = SELECTED;
        if(sing_syst->son_active == true)
        {
            CHK(Mix_PlayChannel(1, click_sound, 0), Mix_GetError());
        }
        if(func_ptr != nullptr)
        {
            func_ptr(sing_syst, this);
        }
    }
}


void Bouton::on_pointer_down(SDL_Event e, SingletonSysteme* const sing_syst)
{
    Selectionnable::on_pointer_down(e, sing_syst);
}

void Bouton::set_selected_if_move(Selectionnable* select_on_up, Selectionnable* select_on_down, Selectionnable* select_on_left, Selectionnable* select_on_right)
{
    Selectionnable::set_selected_if_move(select_on_up, select_on_down, select_on_left, select_on_right);
}


void Bouton::set_selected(Selectionnable* ui)
{
    Selectionnable::set_selected(ui);
}


void Bouton::set_unselected(Selectionnable* previous)
{
    Selectionnable::set_unselected(previous);
}

//désélectionner le bouton actuel et sélectionner le bouton ui
void Bouton::select_new(Selectionnable* ui, SingletonSysteme* const sing_syst)
{
    Selectionnable::select_new(ui, sing_syst);
}
