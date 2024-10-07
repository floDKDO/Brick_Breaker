#ifndef __TUILE__HPP__
#define __TUILE__HPP__

#include "singleton_systeme.hpp"
#include <memory>


class Tuile
{
    public:
        Tuile(const std::string chemin, const int x, const int y, const unsigned int point_de_vie, std::mt19937& e, const SingletonSysteme* const sing_syst);
        Tuile(SDL_Color couleur, const int x, const int y);

        unsigned int point_de_vie; //point de vie max de la tuile
        unsigned int point_de_vie_actuel; //point de vie actuel de la tuile (utile pour les briques de plus de 1 PV)
        SDL_Rect position;
        unsigned int nb_points;
        unsigned int random_value; //pour savoir si quand la tuile est cassée, elle doit générer ou non un bonus/malus

        void draw(SDL_Renderer* const rendu);
        void update(const SingletonSysteme* const sing_syst);

    protected:

    private:
        std::unique_ptr<Texture> texture;
        SDL_Color couleur;
        std::string chemin; //chemin : endroit où la tuile est stockée
        bool une_fois; //pour afficher la fissure quand la brique à 2 pv se fait toucher
};

#endif // __TUILE__HPP__
