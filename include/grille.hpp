#ifndef __GRILLE__HPP__
#define __GRILLE__HPP__

#include <SDL2/SDL.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include "singleton_systeme.hpp"
#include "tuile.hpp"

//place les tuiles selon un fichier ASCII
class Grille
{
    public:
        Grille(const std::string fichier_carte, SingletonSysteme* const sing_syst);

        std::vector<std::unique_ptr<Tuile>> tuiles;

        void init_tuiles(const std::string fichier_carte, SingletonSysteme* const sing_syst);
        void draw(SDL_Renderer* const rendu);
        void update(SingletonSysteme* const sing_syst);

    protected:

    private:
};

#endif // __GRILLE__HPP__
