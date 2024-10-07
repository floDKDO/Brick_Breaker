#ifndef __MENU__PERDU__HPP__
#define __MENU__PERDU__HPP__

#include "menu.hpp"
#include "bouton.hpp"
#include "texte.hpp"

class MenuPerdu : public Menu
{
    public:
        MenuPerdu(const SingletonSysteme* const sing_syst);

        //static sinon probleme de type avec le pointeur de fonction
        static void fonc_bouton_recommencer(SingletonSysteme* const sing_syst, Selectionnable* bouton);
        void reset_selected(void) override;
        Selectionnable* get_selected(void) override;
        void draw(SDL_Renderer* const rendu, SingletonSysteme* const sing_syst);
        void handle_events(const SDL_Event e, SingletonSysteme* const sing_syst) override;


    protected:

    private:
        Texte texte;
        Bouton bouton_recommencer;
};

#endif // __MENU__PERDU__HPP__
