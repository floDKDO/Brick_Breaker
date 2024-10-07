#include "menuJeuTermine.hpp"

//Menu qui apparaît quand tous les niveaux sont terminés
MenuJeuTermine::MenuJeuTermine(const SingletonSysteme* const sing_syst)
:texte_jeu_termine("Jeu terminé !", "./font/VerilySerifMono.otf", 100, BLANC, {266, 100, 500, 200}, sing_syst->renderer->get_renderer())
,texte_points_obtenus("Points obtenus : ", "./font/VerilySerifMono.otf", 50, BLANC, {347, 267, 500, 200}, sing_syst->renderer->get_renderer())
,texte_nb_points_obtenus(" ", "./font/VerilySerifMono.otf", 50, BLANC, {875, 267, 500, 200}, sing_syst->renderer->get_renderer())
,bouton_quitter("./img/base_bouton.png", "./img/texte_quitter.png", {540, 400, 200, 100}, &fonc_bouton_quitter, sing_syst->renderer->get_renderer())
{
    this->bouton_quitter.set_selected(&this->bouton_quitter);
    this->ui.push_back(&(this->bouton_quitter));
}

//fonction exécutée si on clic sur le bouton Quitter
void MenuJeuTermine::fonc_bouton_quitter(SingletonSysteme* const sing_syst, Selectionnable* bouton)
{
    (void)bouton;
    sing_syst->destroy(); //il faut tout clean...
    exit(EXIT_SUCCESS);
}

void MenuJeuTermine::reset_selected(void)
{
    Menu::reset_selected();
}

Selectionnable* MenuJeuTermine::get_selected(void)
{
    return Menu::get_selected();
}

void MenuJeuTermine::draw(SDL_Renderer* const rendu, SingletonSysteme* const sing_syst)
{
    texte_jeu_termine.draw(rendu);
    this->texte_points_obtenus.draw(rendu);
    this->texte_nb_points_obtenus.edit_text(this->texte_nb_points_obtenus.int_to_string(sing_syst->points_obtenus), sing_syst->renderer->get_renderer());
    this->texte_nb_points_obtenus.draw(rendu);
    bouton_quitter.draw(rendu);
}

void MenuJeuTermine::handle_events(const SDL_Event e, SingletonSysteme* const sing_syst)
{
    Menu::handle_events(e, sing_syst);
}
