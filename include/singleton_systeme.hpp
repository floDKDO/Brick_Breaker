#ifndef __SINGLETON__SYSTEME__HPP__
#define __SINGLETON__SYSTEME__HPP__

#include <iostream>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "window.hpp"
#include "renderer.hpp"
#include "surface.hpp"
#include "texture.hpp"

//macros pour gerer les retours de fonctions
#define NCHK(op, type) do { if ((op) == nullptr){std::cerr << type << std::endl; exit(EXIT_FAILURE);} }while(0)
#define CHK(op, type) do { if ((op) < 0){std::cerr << type << std::endl; exit(EXIT_FAILURE);} }while(0)

enum etat_jeu
{
    MENU_PRINCIPAL,
    MENU_OPTIONS,
    EN_JEU,
    MENU_PERDU,
    MENU_FIN_NIVEAU,
    MENU_JEU_TERMINE
};

enum mode_fenetre
{
    FENETRE,
    PLEIN_ECRAN
};

//pour la plateforme
enum mode_deplacement
{
    CLAVIER,
    SOURIS
};

enum type_deplacement
{
    CLASSIQUE,
    CIRCULAIRE
};


const SDL_Color ROUGE = {255, 0, 0, 255};
const SDL_Color VERT = {0, 255, 0, 255};
const SDL_Color BLEU = {0, 0, 255, 255};
const SDL_Color BLANC = {255, 255, 255, 255};
const SDL_Color GRIS = {127, 127, 127, 255};


//singleton
class SingletonSysteme
{
    public:
        static SingletonSysteme& instance()
        {
            static SingletonSysteme* instance = new SingletonSysteme{};
            if(instance == nullptr)
            {
                std::cerr << "Erreur : création singleton" << std::endl;
                exit(EXIT_FAILURE);
            }
            return *instance;
        }

        Window* window;
        Renderer* renderer;

        std::mt19937 e; //pour l'aléatoire

        static const int X_OFFSET_ZONE = 217; //décalage en x de la zone par rapport au côté gauche de l'écran

        static const int LONGUEUR_FENETRE = 1280;
        static const int HAUTEUR_FENETRE = 720;

        etat_jeu etat;
        mode_fenetre mode_fenetre;
        mode_deplacement mode_deplacement;
        type_deplacement type_deplacement;

        bool son_active;

        Mix_Chunk* son_collision_ball_and_brick_or_plateform;
        Mix_Chunk* son_collision_ball_and_wall;
        Mix_Chunk* son_brick_explosion;
        Mix_Chunk* son_bonus_malus;

        int points_obtenus; //quand niveau terminé

        void init();
        void destroy() const;

    protected:

    private:
        SingletonSysteme(){}
};

#endif // __SINGLETON__SYSTEME__HPP__
