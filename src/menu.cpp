#include "menu.hpp"


void Menu::reset_selected(void)
{
    for(auto s : ui)
    {
        s->etat = NORMAL;
    }
}


Selectionnable* Menu::get_selected(void)
{
    Selectionnable* ui_selected;
    for(auto s : ui)
    {
        if(s->etat == SELECTED)
        {
            ui_selected = s;
            break;
        }
    }
    return ui_selected;
}

void Menu::handle_events(const SDL_Event e, SingletonSysteme* const sing_syst)
{
    int x, y; //position x et y de la souris
    SDL_GetMouseState(&x, &y);

    for(auto s : ui)
    {
        if(e.type == SDL_MOUSEMOTION)
        {
            if(s->collision(s->position, x, y) == true)
                this->reset_selected();
        }
        s->handle_events(e, sing_syst);
    }
}
