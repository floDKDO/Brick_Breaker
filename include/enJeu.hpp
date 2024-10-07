#ifndef __EN__JEU__HPP__
#define __EN__JEU__HPP__

#include "singleton_systeme.hpp"
#include "joueur.hpp"
#include "tuile.hpp"
#include "balle.hpp"
#include "bonus.hpp"
#include "malus.hpp"
#include "grille.hpp"
#include "texte.hpp"

#include <vector>
#include <sstream>
#include <memory>

class EnJeu
{
    public:
        EnJeu(SingletonSysteme* const sing_syst);

        static int const offset_zone = 25; //largeur en x et y de la zone = carré entourant la zone de jeu

        void play_sound_collision_ball_and_brick_or_plateform(const SingletonSysteme* const sing_syst);
        void play_sound_collision_ball_and_wall(const SingletonSysteme* const sing_syst);
        void play_sound_brick_explosion(const SingletonSysteme* const sing_syst);
        void play_sound_bonus_malus(const SingletonSysteme* const sing_syst);

        bool test_collision(const SDL_Rect a, const SDL_Rect b)const;
        void draw(SDL_Renderer* const rendu);
        void update(SingletonSysteme* const sing_syst);
        void handle_events(const SDL_Event e, SingletonSysteme* const sing_syst);
        void collision_ball_and_plateform(std::unique_ptr<Balle> &balle, SingletonSysteme* const sing_syst);
        void collision_ball_and_brick(std::unique_ptr<Balle> &balle, SingletonSysteme* const sing_syst);
        void collision_object_and_plateform(std::unique_ptr<Balle> &balle, SingletonSysteme* const sing_syst);
        void collision_between_balls(std::unique_ptr<Balle> &balle, const long long unsigned i, SingletonSysteme* const sing_syst);

        void effet_bonus(const Bonus* bonus, std::unique_ptr<Balle> &balle, SingletonSysteme* const sing_syst);
        void effet_malus(const Malus* malus, std::unique_ptr<Balle> &balle);

        void retirer_bonus_malus(Objet* objet, const Uint32 timer, const int i);

        void handle_ball(std::unique_ptr<Balle> &balle, const int i, SingletonSysteme* const sing_syst);

        void load_level(const int num_level, SingletonSysteme* const sing_syst);

        void check_new_player_position();

        void placer_balles_multi_balles(SingletonSysteme* const sing_syst);

    protected:

    private:
        SDL_Rect zone;
        std::unique_ptr<Texture> texture_zone;

        std::unique_ptr<Texture> texture_fond;
        SDL_Rect fond;

        int nb_balles_restantes;
        int nb_essais_restants; //3 essais par niveau
        unsigned int nb_points_total;
        int niveau_actuel;
        Texte texte_niveau_actuel;
        Texte texte_nb_points_total;
        bool une_fois;

        std::unique_ptr<Texture> texture_balle_nombre_de_vie;

        Joueur joueur;
        std::unique_ptr<Grille> grille;
        std::vector<std::unique_ptr<Balle>> balles;

        std::vector<Objet*> bonus_malus; //bonus ou malus qui apparaît sur l'écran après qu'une brique ait été détruite
        std::vector<std::pair<Objet*, Uint32>> bonus_malus_obtenus; //bonus ou malus récupérés par le joueur, contient également le timer associé au bonu/malus
};

#endif // __EN__JEU__HPP__
