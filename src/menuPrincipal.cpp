#include "menuPrincipal.hpp"

//Menu qui apparaît quand on lance le jeu
MenuPrincipal::MenuPrincipal(const SingletonSysteme* const sing_syst)
:bouton_jouer("./img/base_bouton.png", "./img/texte_jouer.png", {540, 350, 200, 100}, &fonc_bouton_jouer, sing_syst->renderer->get_renderer())
,bouton_options("./img/base_bouton.png", "./img/texte_options.png", {540, 475, 200, 100}, &fonc_bouton_options, sing_syst->renderer->get_renderer())
,bouton_quitter("./img/base_bouton.png", "./img/texte_quitter.png", {540, 600, 200, 100}, &fonc_bouton_quitter, sing_syst->renderer->get_renderer())
{
    this->texte_titre = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), "./img/texte_brick_breaker.png");
    int w, h;
    CHK(SDL_QueryTexture(this->texte_titre->get_texture(), nullptr, nullptr, &w, &h), SDL_GetError());
    this->position_texte_titre = {138, 35, w, h};

    bouton_jouer.set_selected(&bouton_jouer);
    bouton_jouer.set_selected_if_move(nullptr, &bouton_options, nullptr, nullptr);
    bouton_options.set_selected_if_move(&bouton_jouer, &bouton_quitter, nullptr, nullptr);
    bouton_quitter.set_selected_if_move(&bouton_options, nullptr, nullptr, nullptr);

    this->ui.push_back(&(this->bouton_jouer));
    this->ui.push_back(&(this->bouton_options));
    this->ui.push_back(&(this->bouton_quitter));
}


void MenuPrincipal::reset_selected(void)
{
    Menu::reset_selected();
}

Selectionnable* MenuPrincipal::get_selected(void)
{
    return Menu::get_selected();
}

void MenuPrincipal::draw(SDL_Renderer* const rendu, SingletonSysteme* const sing_syst)
{
    (void)sing_syst;
    bouton_jouer.draw(rendu);
    bouton_options.draw(rendu);
    bouton_quitter.draw(rendu);
    CHK(SDL_RenderCopy(rendu, texte_titre->get_texture(), nullptr, &(this->position_texte_titre)), SDL_GetError());
}


void MenuPrincipal::handle_events(const SDL_Event e, SingletonSysteme* const sing_syst)
{
    Menu::handle_events(e, sing_syst);
}


void MenuPrincipal::fonc_bouton_quitter(SingletonSysteme* const sing_syst, Selectionnable* bouton)
{
    (void)bouton;
    sing_syst->destroy(); //il faut tout clean...
    exit(EXIT_SUCCESS);
}

void MenuPrincipal::fonc_bouton_options(SingletonSysteme* const sing_syst, Selectionnable* bouton)
{
    (void)bouton;
    sing_syst->etat = MENU_OPTIONS;
}

void MenuPrincipal::fonc_bouton_jouer(SingletonSysteme* const sing_syst, Selectionnable* bouton)
{
    (void)bouton;
    sing_syst->etat = EN_JEU;
}
