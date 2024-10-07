#include "menuOptions.hpp"

//Menu qui apparaît quand on clic sur le bouton Options du menu Principal
MenuOptions::MenuOptions(const SingletonSysteme* const sing_syst)
:bouton_options_fenetre("./img/base_bouton.png", "./img/texte_fenetre.png", {600, 600, 200, 100}, &fonc_bouton_options_fenetre, sing_syst->renderer->get_renderer())
,bouton_options_retour("./img/base_bouton.png", "./img/texte_retour.png", {100, 600, 200, 100}, &fonc_bouton_options_retour, sing_syst->renderer->get_renderer())
,bouton_options_choix("./img/base_bouton.png", "./img/texte_souris.png", {600, 100, 150, 60}, &fonc_choix, sing_syst->renderer->get_renderer())
,toggle_sound("./img/base_toggle.png", "./img/texte_son.png", {650, 343, 100, 100}, &fonc_toggle_son, sing_syst->son_active, sing_syst->renderer->get_renderer())
{
    this->texte_choix = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), "./img/texte_choix.png");
    int w, h;
    CHK(SDL_QueryTexture(this->texte_choix->get_texture(), nullptr, nullptr, &w, &h), SDL_GetError());
    this->position_texte_choix = {600, 50, w, h};
    this->texte_mode_ecran = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), "./img/texte_mode_ecran.png");
    CHK(SDL_QueryTexture(this->texte_mode_ecran->get_texture(), nullptr, nullptr, &w, &h), SDL_GetError());
    this->position_texte_mode_ecran = {600, 550, w, h};

    bouton_options_fenetre.set_selected_if_move(&toggle_sound, nullptr, &bouton_options_retour, nullptr);
    bouton_options_retour.set_selected_if_move(&bouton_options_choix, nullptr, nullptr, &bouton_options_fenetre);
    bouton_options_retour.set_selected(&bouton_options_retour);
    toggle_sound.set_selected_if_move(&bouton_options_choix, &bouton_options_fenetre, &bouton_options_retour, nullptr);
    bouton_options_choix.set_selected_if_move(nullptr, &toggle_sound, &bouton_options_retour, nullptr);

    this->ui.push_back(&(this->bouton_options_fenetre));
    this->ui.push_back(&(this->bouton_options_retour));
    this->ui.push_back(&(this->bouton_options_choix));
    this->ui.push_back(&(this->toggle_sound));
}


void MenuOptions::reset_selected(void)
{
    Menu::reset_selected();
}

Selectionnable* MenuOptions::get_selected(void)
{
    return Menu::get_selected();
}

void MenuOptions::draw(SDL_Renderer* const rendu, SingletonSysteme* const sing_syst)
{
    (void)sing_syst;
    for(Selectionnable* s : ui)
    {
        s->draw(rendu);
    }

    CHK(SDL_RenderCopy(rendu, texte_choix->get_texture(), nullptr, &(this->position_texte_choix)), SDL_GetError());
    CHK(SDL_RenderCopy(rendu, texte_mode_ecran->get_texture(), nullptr, &(this->position_texte_mode_ecran)), SDL_GetError());
}


void MenuOptions::handle_events(const SDL_Event e, SingletonSysteme* const sing_syst)
{
    Menu::handle_events(e, sing_syst);
}


void MenuOptions::fonc_bouton_options_retour(SingletonSysteme* const sing_syst, Selectionnable* bouton)
{
    (void)bouton;
    sing_syst->etat = MENU_PRINCIPAL;
}

//Plein écran ou mode fenêtré
void MenuOptions::fonc_bouton_options_fenetre(SingletonSysteme* const sing_syst, Selectionnable* bouton)
{
    Uint32 mask_window = SDL_GetWindowFlags(sing_syst->window->get_window());
    if(mask_window & SDL_WINDOW_FULLSCREEN) //si la fenetre est en plein ecran
    {
        CHK(SDL_SetWindowFullscreen(sing_syst->window->get_window(), 0), SDL_GetError());
        sing_syst->mode_fenetre = FENETRE;
    }
    else //si la fenetre est en mode fenetre
    {
        CHK(SDL_SetWindowFullscreen(sing_syst->window->get_window(), SDL_WINDOW_FULLSCREEN), SDL_GetError());
        sing_syst->mode_fenetre = PLEIN_ECRAN;
    }

    if(sing_syst->mode_fenetre == FENETRE)
    {
        if((dynamic_cast<Bouton*>(bouton)->image_texte = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), "./img/texte_fenetre.png")) == nullptr)
        {
            std::cerr << "Erreur : dynamic_cast." << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else if(sing_syst->mode_fenetre == PLEIN_ECRAN)
    {
        if((dynamic_cast<Bouton*>(bouton)->image_texte = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), "./img/texte_plein_ecran.png")) == nullptr)
        {
            std::cerr << "Erreur : dynamic_cast." << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

//déplacer la plateforme avec la souris ou le clavier
void MenuOptions::fonc_choix(SingletonSysteme* const sing_syst, Selectionnable* bouton)
{
    if(sing_syst->mode_deplacement == CLAVIER)
    {
        if((dynamic_cast<Bouton*>(bouton)->image_texte = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), "./img/texte_souris.png")) == nullptr)
        {
            std::cerr << "Erreur : dynamic_cast." << std::endl;
            exit(EXIT_FAILURE);
        }
        sing_syst->mode_deplacement = SOURIS;
    }
    else if(sing_syst->mode_deplacement == SOURIS)
    {
        if((dynamic_cast<Bouton*>(bouton)->image_texte = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), "./img/texte_clavier.png")) == nullptr)
        {
            std::cerr << "Erreur : dynamic_cast." << std::endl;
            exit(EXIT_FAILURE);
        }
        sing_syst->mode_deplacement = CLAVIER;
    }
}


void MenuOptions::fonc_toggle_son(SingletonSysteme* const sing_syst, Selectionnable* bouton)
{
    (void)bouton;
    sing_syst->son_active = !(sing_syst->son_active);
}
