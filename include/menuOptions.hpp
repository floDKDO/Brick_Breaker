#ifndef __MENU__OPTIONS__HPP__
#define __MENU__OPTIONS__HPP__

#include "menu.hpp"
#include "bouton.hpp"
#include "texte.hpp"
#include "toggle.hpp"

class MenuOptions : public Menu
{
    public:
        MenuOptions(const SingletonSysteme* const sing_syst);

        //static sinon probleme de type avec le pointeur de fonction
        static void fonc_bouton_options_retour(SingletonSysteme* const sing_syst, Selectionnable* bouton);
        static void fonc_choix(SingletonSysteme* const sing_syst, Selectionnable* bouton);
        static void fonc_toggle_son(SingletonSysteme* const sing_syst, Selectionnable* bouton);
        static void fonc_bouton_options_fenetre(SingletonSysteme* const sing_syst, Selectionnable* bouton);
        void reset_selected(void) override;
        Selectionnable* get_selected(void) override;
        void draw(SDL_Renderer* const rendu, SingletonSysteme* const sing_syst);
        void handle_events(const SDL_Event e, SingletonSysteme* const sing_syst) override;

    protected:

    private:
        Bouton bouton_options_fenetre;
        Bouton bouton_options_retour;
        Bouton bouton_options_choix;
        Toggle toggle_sound;
        std::unique_ptr<Texture> texte_choix;
        SDL_Rect position_texte_choix;
        std::unique_ptr<Texture> texte_mode_ecran;
        SDL_Rect position_texte_mode_ecran;
};


#endif // MENUOPTIONS_HPP
