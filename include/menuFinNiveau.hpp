#ifndef __MENU__FIN__NIVEAU__HPP__
#define __MENU__FIN__NIVEAU__HPP__

#include "menu.hpp"
#include "bouton.hpp"
#include "texte.hpp"

class MenuFinNiveau : public Menu
{
    public:
        MenuFinNiveau(const SingletonSysteme* const sing_syst);

        //static sinon probleme de type avec le pointeur de fonction
        static void fonc_bouton_prochain_niveau(SingletonSysteme* const sing_syst, Selectionnable* bouton);
        void reset_selected(void) override;
        Selectionnable* get_selected(void) override;
        void draw(SDL_Renderer* const rendu, SingletonSysteme* const sing_syst);
        void handle_events(const SDL_Event e, SingletonSysteme* const sing_syst) override;

    protected:

    private:
        Texte texte_fin_niveau;
        Texte texte_points_obtenus;
        Texte texte_nb_points_obtenus;
        Bouton bouton_prochain_niveau;
};

#endif // __MENU__FIN__NIVEAU__HPP__
