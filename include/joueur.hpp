#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include "tuile.hpp"
#include "singleton_systeme.hpp"

#include <array>

enum taille_plateforme
{
    PETITE,
    NORMALE,
    GRANDE
};

class Joueur // = plateforme
{
    public:

        Joueur(const SingletonSysteme* const sing_syst);

        static const int VITESSE_DEPLACEMENT = 18;
        SDL_Rect position;
        enum taille_plateforme taille_plateforme;

        void reset_all_values();
        void reset_position(SingletonSysteme* sing_syst);
        void set_value(const int indice);
        void draw(SDL_Renderer* const rendu) const;
        void handle_events(const SDL_Event e, const SingletonSysteme* const sing_syst);
        void update(const SingletonSysteme* const sing_syst);

        void set_size_big();
        void set_size_small();
        void set_size_normal();

    protected:

    private:
        std::array<std::unique_ptr<Texture>, 3> texture;
        std::array<bool, 2> dep; //dep[0] = GAUCHE, dep[1] = DROITE
        float angle; //pour mouvement circulaire
};

#endif // JOUEUR_HPP
