#include "menuPerdu.hpp"

//Menu qui apparaît quand on a plus de balle, donc qu'on perd le niveau
MenuPerdu::MenuPerdu(const SingletonSysteme* const sing_syst)
:texte("Perdu !", "./font/VerilySerifMono.otf", 100, BLANC, {440, 100, 500, 200}, sing_syst->renderer->get_renderer())
,bouton_recommencer("./img/base_bouton.png", "./img/texte_recommencer.png", {540, 400, 200, 100}, &fonc_bouton_recommencer, sing_syst->renderer->get_renderer())
{
    bouton_recommencer.set_selected(&bouton_recommencer);
    bouton_recommencer.set_selected_if_move(nullptr, nullptr, nullptr, nullptr);

    this->ui.push_back(&(this->bouton_recommencer));
}

void MenuPerdu::fonc_bouton_recommencer(SingletonSysteme* const sing_syst, Selectionnable* bouton)
{
    (void)bouton;
    sing_syst->etat = EN_JEU;
}

void MenuPerdu::reset_selected(void)
{
    Menu::reset_selected();
}

Selectionnable* MenuPerdu::get_selected(void)
{
    return Menu::get_selected();
}

void MenuPerdu::draw(SDL_Renderer* const rendu, SingletonSysteme* const sing_syst)
{
    (void)sing_syst;
    this->texte.draw(rendu);
    this->bouton_recommencer.draw(rendu);
}

void MenuPerdu::handle_events(const SDL_Event e, SingletonSysteme* const sing_syst)
{
    Menu::handle_events(e, sing_syst);
}
