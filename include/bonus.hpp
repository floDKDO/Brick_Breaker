#ifndef __BONUS__HPP__
#define __BONUS__HPP__

#include "objet.hpp"

enum sorte_bonus
{
    MULTI_BALLES,
    GRANDE_BALLE,
    GRANDE_PLATEFORME
};

class Bonus : public Objet
{
    public:
        Bonus(const int x, const int y, std::mt19937& e, const SingletonSysteme* const sing_syst);
        enum sorte_bonus sorte_bonus;

        void draw(SDL_Renderer* const rendu) const override;
        void update() override;

    protected:

    private:
};

#endif // __BONUS__HPP__
