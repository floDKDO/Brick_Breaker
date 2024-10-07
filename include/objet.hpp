#ifndef __OBJET__HPP__
#define __OBJET__HPP__

#include "singleton_systeme.hpp"
#include <memory>

class Objet
{
    public:
        Objet(){}
        virtual ~Objet(){}

        static const int SPEED_OBJET = 4;
        SDL_Rect position;

        virtual void draw(SDL_Renderer* const rendu) const = 0;
        virtual void update() = 0;

    protected:
        std::unique_ptr<Texture> texture;

    private:
};

#endif // __OBJET__HPP__
