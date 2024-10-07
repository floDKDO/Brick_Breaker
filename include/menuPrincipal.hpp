#ifndef __MENU__PRINCIPAL__HPP__
#define __MENU__PRINCIPAL__HPP__

#include "menu.hpp"
#include "bouton.hpp"

class MenuPrincipal : public Menu
{
    public:
        MenuPrincipal(const SingletonSysteme* const sing_syst);

        //static sinon probleme de type avec le pointeur de fonction
        static void fonc_bouton_quitter(SingletonSysteme* const sing_syst, Selectionnable* bouton);
        static void fonc_bouton_options(SingletonSysteme* const sing_syst, Selectionnable* bouton);
        static void fonc_bouton_jouer(SingletonSysteme* const sing_syst, Selectionnable* bouton);
        void reset_selected(void) override;
        Selectionnable* get_selected(void) override;
        void draw(SDL_Renderer* const rendu, SingletonSysteme* const sing_syst);
        void handle_events(const SDL_Event e, SingletonSysteme* const sing_syst) override;

    protected:

    private:
        Bouton bouton_jouer;
        Bouton bouton_options;
        Bouton bouton_quitter;

        std::unique_ptr<Texture> texte_titre;
        SDL_Rect position_texte_titre;
};

#endif // __MENU__PRINCIPAL__HPP__
