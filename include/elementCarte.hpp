#ifndef __ELEMENT__CARTE__HPP__
#define __ELEMENT__CARTE__HPP__

#include "singleton_systeme.hpp"


//classe virtuelle pure pour chaque élément constituant une carte (tuile, objet...)
class ElementCarte
{
    public:
        ElementCarte(){}

        SDL_Rect position;
        std::string chemin;
        SDL_Texture* texture;

        virtual void draw(SDL_Renderer* rendu) = 0;
        virtual void handleEvents(SDL_Event e, SingletonSysteme* sing_syst) = 0;
        virtual void update(const SingletonSysteme* sing_syst) = 0;

    protected:

    private:
};

#endif // __ELEMENT__CARTE__HPP__
