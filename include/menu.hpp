#ifndef __MENU__HPP__
#define __MENU__HPP__

#include <vector>

#include "selectionnable.hpp"
#include "singleton_systeme.hpp"

class Menu
{
    public:
        Menu(){}
        virtual ~Menu(){}

        virtual void reset_selected(void);
        virtual Selectionnable* get_selected(void);
        virtual void draw(SDL_Renderer* const rendu, SingletonSysteme* const sing_syst) = 0;
        virtual void handle_events(const SDL_Event e, SingletonSysteme* const sing_syst) = 0;

    protected:
        std::vector<Selectionnable*> ui; //contient tous les boutons/toggle du menu

    private:
};

#endif // __MENU__HPP__
