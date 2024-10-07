#ifndef __BALLE__HPP__
#define __BALLE__HPP__

#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <memory>

#include "singleton_systeme.hpp"

class Balle
{
    public:
        Balle(int x, int y, SingletonSysteme* const sing_syst); //Constructeur pour les balles générées par le bonus MULTI_BALLES
        Balle(SingletonSysteme* const sing_syst); //Constructeur pour la balle générée au début d'un niveau
        SDL_Rect position;
        int velocity_x, velocity_y;
        static const int SPEED = 5;
        static const int TAILLE_NORMALE = 30;

        void draw(SDL_Renderer* const rendu) const;
        void update();
        bool is_big();
        bool is_small();
        void set_size_big();
        void set_size_small();
        void set_size_normal();

    protected:

    private:
        std::string chemin; //fichier
        std::unique_ptr<Texture> texture;
};

#endif // __BALLE__HPP__
