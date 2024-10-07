#include "menuFinNiveau.hpp"

//Menu qui apparaît quand un niveau est terminé et qu'il y a un niveau après celui qu'on vient de terminer
MenuFinNiveau::MenuFinNiveau(const SingletonSysteme* const sing_syst)
:texte_fin_niveau("Niveau terminé !", "./font/VerilySerifMono.otf", 100, BLANC, {172, 100, 500, 200}, sing_syst->renderer->get_renderer())
,texte_points_obtenus("Points obtenus : ", "./font/VerilySerifMono.otf", 50, BLANC, {347, 267, 500, 200}, sing_syst->renderer->get_renderer())
,texte_nb_points_obtenus(" ", "./font/VerilySerifMono.otf", 50, BLANC, {875, 267, 500, 200}, sing_syst->renderer->get_renderer())
,bouton_prochain_niveau("./img/base_bouton.png", "./img/texte_prochain_niveau.png", {540, 400, 200, 100}, &fonc_bouton_prochain_niveau, sing_syst->renderer->get_renderer())
{
    this->bouton_prochain_niveau.set_selected(&this->bouton_prochain_niveau);
    this->bouton_prochain_niveau.set_selected_if_move(nullptr, nullptr, nullptr, nullptr);

    this->ui.push_back(&(this->bouton_prochain_niveau));
}

//fonction exécutée si on clic sur le bouton Prochain Niveau
void MenuFinNiveau::fonc_bouton_prochain_niveau(SingletonSysteme* const sing_syst, Selectionnable* bouton)
{
    (void)bouton;
    sing_syst->etat = EN_JEU;
}

void MenuFinNiveau::reset_selected(void)
{
    Menu::reset_selected();
}

Selectionnable* MenuFinNiveau::get_selected(void)
{
    return Menu::get_selected();
}

void MenuFinNiveau::draw(SDL_Renderer* const rendu, SingletonSysteme* const sing_syst)
{
    this->texte_fin_niveau.draw(rendu);
    this->texte_points_obtenus.draw(rendu);
    this->texte_nb_points_obtenus.edit_text(this->texte_nb_points_obtenus.int_to_string(sing_syst->points_obtenus), sing_syst->renderer->get_renderer());
    this->texte_nb_points_obtenus.draw(rendu);
    this->bouton_prochain_niveau.draw(rendu);
}

void MenuFinNiveau::handle_events(const SDL_Event e, SingletonSysteme* const sing_syst)
{
    Menu::handle_events(e, sing_syst);
}
