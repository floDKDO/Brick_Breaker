#ifndef __MALUS__HPP__
#define __MALUS__HPP__

#include "objet.hpp"

enum sorte_malus
{
    PETITE_BALLE,
    PETITE_PLATEFORME
};

class Malus : public Objet
{
    public:
        Malus(const int x, const int y, std::mt19937& e, const SingletonSysteme* const sing_syst);
        enum sorte_malus sorte_malus;

        void draw(SDL_Renderer* const rendu) const override;
        void update() override;

    protected:

    private:
};

#endif // __MALUS__HPP__
