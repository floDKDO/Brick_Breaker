#include "enJeu.hpp"

EnJeu::EnJeu(SingletonSysteme* const sing_syst)
:zone{189, 0, 902, sing_syst->HAUTEUR_FENETRE},
fond{0, 0, sing_syst->LONGUEUR_FENETRE, sing_syst->HAUTEUR_FENETRE},
nb_balles_restantes(1),
nb_essais_restants(3),
nb_points_total(0),
niveau_actuel(1), //lvl 1
texte_niveau_actuel("Niveau 1", "./font/VerilySerifMono.otf", 30, BLANC, {24, 30, 150, 60}, sing_syst->renderer->get_renderer()),
texte_nb_points_total("0", "./font/VerilySerifMono.otf", 50, BLANC, {1120, 650, 150, 60}, sing_syst->renderer->get_renderer()),
joueur(sing_syst)
{
    this->balles.reserve(20);
    if(sing_syst->type_deplacement == CLASSIQUE)
    {
        this->balles.emplace_back(std::make_unique<Balle>(sing_syst)); //balle de début
    }
    this->texture_zone = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), "./img/zone.png");
    this->texture_fond = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), "./img/bg.png");
    this->texture_balle_nombre_de_vie = std::make_unique<Texture>(sing_syst->renderer->get_renderer(), "./img/balle.png");
    this->grille = std::make_unique<Grille>("./grille1.txt", sing_syst);
    //load_level(4, sing_syst); //pour niveau circulaire
}

//test collision entre deux SDL_Rect
bool EnJeu::test_collision(const SDL_Rect a, const SDL_Rect b)const
{
    if(a.y + a.h > b.y
    && a.y < b.y + b.h
    && a.x + a.w > b.x
    && a.x < b.x + b.w)
    {
        return true;
    }
    else return false;
}


void EnJeu::load_level(const int num_level, SingletonSysteme* const sing_syst)
{
    this->balles.clear();
    this->bonus_malus.clear();
    this->bonus_malus_obtenus.clear();
    this->nb_balles_restantes = 1;
    this->nb_essais_restants = 3;
    this->nb_points_total = 0;
    this->texte_nb_points_total.edit_text(this->texte_nb_points_total.int_to_string(this->nb_points_total), sing_syst->renderer->get_renderer());

    this->joueur.reset_position(sing_syst);
    if(num_level == 1)
    {
        this->grille = std::make_unique<Grille>("./grille1.txt", sing_syst);
    }
    else if(num_level == 2)
    {
        this->grille = std::make_unique<Grille>("./grille2.txt", sing_syst);
    }
    else if(num_level == 3)
    {
        this->grille = std::make_unique<Grille>("./grille3.txt", sing_syst);
    }
    /*else if(num_level == 4)
    {
        sing_syst->type_deplacement = CIRCULAIRE;
        this->joueur = Joueur(sing_syst);
        this->grille = std::make_unique<Grille>("", sing_syst);
    }*/
    this->texte_niveau_actuel.edit_text("Niveau " + this->texte_niveau_actuel.int_to_string(this->niveau_actuel), sing_syst->renderer->get_renderer());
    if(num_level != 4)
    {
        this->balles.emplace_back((std::make_unique<Balle>(sing_syst))); //balle de début
    }
}


void EnJeu::play_sound_collision_ball_and_brick_or_plateform(const SingletonSysteme* const sing_syst)
{
    if(sing_syst->son_active == true)
    {
        CHK(Mix_PlayChannel(1, sing_syst->son_collision_ball_and_brick_or_plateform, 0), Mix_GetError());
    }
}


void EnJeu::play_sound_brick_explosion(const SingletonSysteme* const sing_syst)
{
    if(sing_syst->son_active == true)
    {
        CHK(Mix_PlayChannel(1, sing_syst->son_brick_explosion, 0), Mix_GetError());
    }
}


void EnJeu::play_sound_bonus_malus(const SingletonSysteme* const sing_syst)
{
    if(sing_syst->son_active == true)
    {
        CHK(Mix_PlayChannel(1, sing_syst->son_bonus_malus, 0), Mix_GetError());
    }
}


void EnJeu::play_sound_collision_ball_and_wall(const SingletonSysteme* const sing_syst)
{
    if(sing_syst->son_active == true)
    {
        CHK(Mix_PlayChannel(1, sing_syst->son_collision_ball_and_wall, 0), Mix_GetError());
    }
}

void EnJeu::collision_ball_and_plateform(std::unique_ptr<Balle> &balle, SingletonSysteme* const sing_syst)
{
    if(balle->position.y + balle->position.h >= this->joueur.position.y //BAS
    && balle->position.x <= this->joueur.position.x + this->joueur.position.w //GAUCHE
    && balle->position.x + balle->position.w >= this->joueur.position.x //DROITE
    && balle->position.y <= this->joueur.position.y + this->joueur.position.h) //HAUT
    {
        /*
        Plateforme divisée en 5 parties. Selon la partie sur laquelle la balle entre en collision, la modification en x et y de la balle est adaptée
        */

        int taille_cinquieme = this->joueur.position.w / 5;
        int new_velocity_X = balle->velocity_x;
        int new_velocity_Y = balle->velocity_y;

        if(balle->position.y + balle->position.h > this->joueur.position.y + 10) //coté joueur, +10 pour dire que la balle est vraiment en dessous du dessus du joueur
        {
            if(balle->position.x + balle->position.w < this->joueur.position.x + taille_cinquieme || balle->position.x >= this->joueur.position.x + 4*taille_cinquieme)
            {
                new_velocity_X = -balle->velocity_x; //inverser le X de la balle
                new_velocity_Y = balle->velocity_y; //conserver la vitesse en Y de la balle
                play_sound_collision_ball_and_brick_or_plateform(sing_syst);
            }
        }
        else //sur le joueur
        {
            if(balle->position.x + balle->position.w < this->joueur.position.x + taille_cinquieme) //Premier cinquième
            {
                new_velocity_X = balle->SPEED * -1;
            }
            else if(balle->position.x + balle->position.w >= this->joueur.position.x + taille_cinquieme * 1 && balle->position.x + balle->position.w < this->joueur.position.x + 2 * taille_cinquieme) //Deuxième cinquième
            {
                new_velocity_X = balle->SPEED * -0.5;
            }
            else if(balle->position.x + balle->position.w >= this->joueur.position.x + 2*taille_cinquieme && balle->position.x + balle->position.w < this->joueur.position.x + 2.5 * taille_cinquieme) //Troisième cinquième (plus petit que les autres)
            {
                new_velocity_X = balle->SPEED * 0;
            }
            else if(balle->position.x + balle->position.w >= this->joueur.position.x + 2.5*taille_cinquieme && balle->position.x + balle->position.w < this->joueur.position.x + 4 * taille_cinquieme) //Quatrième cinquième
            {
                new_velocity_X = balle->SPEED * 0.5;
            }
            else if(balle->position.x + balle->position.w >= this->joueur.position.x + 4*taille_cinquieme) //Cinquième cinquième
            {
                new_velocity_X = balle->SPEED * 1;
            }
            new_velocity_Y = balle->SPEED * -1;
            play_sound_collision_ball_and_brick_or_plateform(sing_syst);
        }
        balle->velocity_x = new_velocity_X;
        balle->velocity_y = new_velocity_Y;
    }
}

//S'assurer que le joueur ne sorte pas de la zone = carré entourant la zone de jeu
void EnJeu::check_new_player_position()
{
    if(this->joueur.position.x <= this->zone.x + offset_zone)
    {
        this->joueur.position.x = this->zone.x + offset_zone;
    }
    else if(this->joueur.position.x + this->joueur.position.w >= this->zone.x + this->zone.w - offset_zone)
    {
        this->joueur.position.x = this->zone.x + this->zone.w - offset_zone - this->joueur.position.w;
    }
}

//ajouter deux balles après récupération d'un bonus MULTI_BALLES
void EnJeu::placer_balles_multi_balles(SingletonSysteme* const sing_syst)
{
    //prendre une balle sur le terrain, les 2 autres balles seront proches d'elle
    auto& dummy = this->balles[0];

    const int offset = 100;

    int moitie_zone_w = ((zone.x + zone.w - this->offset_zone) - (zone.x + this->offset_zone)) / 2;
    int moitie_zone_h = ((zone.y + zone.h) - (zone.y + this->offset_zone)) / 2;

    int x_offset, y_offset;

    if(dummy->position.x < zone.x + this->offset_zone + moitie_zone_w) //moitié gauche => les 2 balles générées seront à sa droite
    {
        x_offset = offset;
    }
    else x_offset = -offset; //moitié droite => les 2 balles générées seront à sa gauche

    if(dummy->position.y >= zone.y + this->offset_zone + moitie_zone_h) //moitié basse => les 2 balles générées seront au-dessus
    {
        y_offset = -offset;
    }
    else y_offset = offset; //moitié haute => les 2 balles générées seront en-dessous

    int x_balle_1 = dummy->position.x + x_offset + dummy->position.w + 1; //+1 pour ne pas que les balles générées soient "dans" la balle dummy
    int x_balle_2 = dummy->position.x + x_offset;

    int y_balle_1 = dummy->position.y + y_offset + dummy->position.h + 1;
    int y_balle_2 = dummy->position.y + y_offset;

    //s'assurer que les 2 balles soient dans la zone = carré entourant la zone de jeu
    if(x_balle_1 <= zone.x + offset_zone)
        x_balle_1 = zone.x + offset; //offset et pas offset_zone pour ne pas coller les balles à la zone
    else if(x_balle_1 + dummy->position.w >= zone.x + zone.w - offset_zone)
        x_balle_1 = zone.x + zone.w - offset - dummy->position.w;

    if(x_balle_2 <= zone.x + offset_zone)
        x_balle_2 = zone.x + offset;
    else if(x_balle_2 + dummy->position.w >= zone.x + zone.w - offset_zone)
        x_balle_2 = zone.x + zone.w - offset - dummy->position.w;

    if(y_balle_1 <= zone.y + offset_zone)
        y_balle_1 = zone.y + offset;
    else if(y_balle_1 + dummy->position.h >= zone.y + zone.h)
        y_balle_1 = zone.y + zone.h - dummy->position.h;

    if(y_balle_2 <= zone.y + offset_zone)
        y_balle_2 = zone.y + offset;
    else if(y_balle_2 + dummy->position.h >= zone.y + zone.h)
        y_balle_2 = zone.y + zone.h - dummy->position.h;

    this->balles.emplace_back(std::make_unique<Balle>(x_balle_1, y_balle_1, sing_syst)); //balle 2
    this->balles.emplace_back(std::make_unique<Balle>(x_balle_2, y_balle_2, sing_syst)); //balle 3
    this->nb_balles_restantes += 2;
}


void EnJeu::effet_bonus(const Bonus* bonus, std::unique_ptr<Balle> &balle, SingletonSysteme* const sing_syst)
{
    if(bonus->sorte_bonus == GRANDE_BALLE)
    {
        balle->set_size_big();
    }
    else if(bonus->sorte_bonus == GRANDE_PLATEFORME)
    {
        this->joueur.set_size_big();
        check_new_player_position();
    }
    else if(bonus->sorte_bonus == MULTI_BALLES)
    {
        placer_balles_multi_balles(sing_syst);
    }
}


void EnJeu::effet_malus(const Malus* malus, std::unique_ptr<Balle> &balle)
{
    if(malus->sorte_malus == PETITE_BALLE)
    {
        balle->set_size_small();
    }
    else if(malus->sorte_malus == PETITE_PLATEFORME)
    {
        this->joueur.set_size_small();
        check_new_player_position();
    }
}


void EnJeu::collision_ball_and_brick(std::unique_ptr<Balle> &balle, SingletonSysteme* const sing_syst)
{
    for(long long unsigned int j = 0; j < this->grille->tuiles.size(); j++)
    {
        if(test_collision(balle->position, this->grille->tuiles[j]->position))
        {
            int ball_center_x = balle->position.x + balle->position.w / 2;
            int ball_center_y = balle->position.y + balle->position.h / 2;
            int brick_center_x = this->grille->tuiles[j]->position.x + this->grille->tuiles[j]->position.w / 2;
            int brick_center_y = this->grille->tuiles[j]->position.y + this->grille->tuiles[j]->position.h / 2;

            int delta_x = ball_center_x - brick_center_x;
            int delta_y = ball_center_y - brick_center_y;

            if(std::abs(delta_x) != std::abs(delta_y))
            {
                if(std::abs(delta_x) > std::abs(delta_y))
                {
                    if((delta_x > 0 && (balle->velocity_x < 0 && (balle->velocity_y > 0 || balle->velocity_y < 0))) //DROITE
                    || (delta_x <= 0 && (balle->velocity_x > 0 && (balle->velocity_y > 0 || balle->velocity_y < 0)))) //GAUCHE
                    {
                        balle->velocity_x *= -1;
                    }
                    else balle->velocity_y *= -1; //BAS
                }
                else if(std::abs(delta_x) < std::abs(delta_y)) //BAS ou HAUT
                {
                    balle->velocity_y *= -1;
                }
            }
            else //si delta_x et delta_y sont égaux, alors la balle a tapé un coin du bloc
            {
                balle->velocity_x *= -1;
                balle->velocity_y *= -1;
            }
            this->grille->tuiles[j]->point_de_vie_actuel -= 1;

            if(this->grille->tuiles[j]->point_de_vie_actuel == 0)
            {
                play_sound_brick_explosion(sing_syst);
                this->nb_points_total += this->grille->tuiles[j]->nb_points;
                this->texte_nb_points_total.edit_text(this->texte_nb_points_total.int_to_string(this->nb_points_total), sing_syst->renderer->get_renderer());
                if(this->grille->tuiles[j]->random_value >= 50) //une chance sur deux que le bloc contienne un bonus ou un malus
                {
                    if(this->grille->tuiles[j]->random_value % 2 == 0) //une chance sur deux d'avoir un bonus ou un malus
                        this->bonus_malus.emplace_back(new Bonus{this->grille->tuiles[j]->position.x + ((this->grille->tuiles[j]->position.w - 42)/2), this->grille->tuiles[j]->position.y + ((this->grille->tuiles[j]->position.w - 42)/2), sing_syst->e, sing_syst});
                    else this->bonus_malus.emplace_back(new Malus{this->grille->tuiles[j]->position.x + ((this->grille->tuiles[j]->position.w - 42)/2), this->grille->tuiles[j]->position.y + ((this->grille->tuiles[j]->position.w - 42)/2), sing_syst->e, sing_syst});
                }
                this->grille->tuiles.erase(this->grille->tuiles.begin() + j);
            }
            else play_sound_collision_ball_and_brick_or_plateform(sing_syst);
            break;
        }
    }
}


//objet = bonus ou malus
void EnJeu::collision_object_and_plateform(std::unique_ptr<Balle> &balle, SingletonSysteme* const sing_syst)
{
    for(long long unsigned int i = 0; i < this->bonus_malus.size(); i++)
    {
        if(test_collision(joueur.position, this->bonus_malus[i]->position))
        {
            Uint32 timer = 0; //durée du bonus/malus
            play_sound_bonus_malus(sing_syst);

            //appliquer le bonus/malus !
            if(dynamic_cast<Bonus*>(this->bonus_malus[i]) != nullptr) //if bonus
            {
                Bonus* bonus = dynamic_cast<Bonus*>(this->bonus_malus[i]);
                for(long long unsigned int j = 0; j < this->bonus_malus_obtenus.size(); j++)
                {
                    if(dynamic_cast<Bonus*>(this->bonus_malus_obtenus[j].first) != nullptr)
                    {
                        Bonus* bonus_obtenu = dynamic_cast<Bonus*>(this->bonus_malus_obtenus[j].first);
                        if(bonus_obtenu->sorte_bonus == bonus->sorte_bonus && bonus->sorte_bonus != MULTI_BALLES) //bonus déjà actif, ne pas l'activer deux fois !
                        {
                            this->bonus_malus.erase(this->bonus_malus.begin() + i);
                            return;
                        }
                    }
                    else if(dynamic_cast<Malus*>(this->bonus_malus_obtenus[j].first) != nullptr)
                    {
                        Malus* malus_obtenu = dynamic_cast<Malus*>(this->bonus_malus_obtenus[j].first);
                        if((bonus->sorte_bonus == GRANDE_PLATEFORME && malus_obtenu->sorte_malus == PETITE_PLATEFORME) //la plateforme était petite. Au lieu de lui donner sa taille normale, elle devient grande
                        || (bonus->sorte_bonus == GRANDE_BALLE && malus_obtenu->sorte_malus == PETITE_BALLE)) //la balle était petite. Au lieu de lui donner sa taille normale, elle devient grande
                        {
                            this->bonus_malus_obtenus.erase(this->bonus_malus_obtenus.begin() + j);
                            effet_bonus(bonus, balle, sing_syst);
                        }
                    }
                }
                effet_bonus(bonus, balle, sing_syst);
                if(bonus->sorte_bonus != MULTI_BALLES) //timer = 0 pour multi_balles
                {
                    timer = SDL_GetTicks() + 10000; //10 secondes
                }
            }
            else if(dynamic_cast<Malus*>(this->bonus_malus[i]) != nullptr) //if malus
            {
                Malus* malus = dynamic_cast<Malus*>(this->bonus_malus[i]);
                for(long long unsigned int j = 0; j < this->bonus_malus_obtenus.size(); j++)
                {
                    if(dynamic_cast<Malus*>(this->bonus_malus_obtenus[j].first) != nullptr)
                    {
                        Malus* malus_obtenu = dynamic_cast<Malus*>(this->bonus_malus_obtenus[j].first);
                        if(malus_obtenu->sorte_malus == malus->sorte_malus) //bonus déjà actif, ne pas l'activer deux fois !
                        {
                            this->bonus_malus.erase(this->bonus_malus.begin() + i);
                            return;
                        }
                    }
                    else if(dynamic_cast<Bonus*>(this->bonus_malus_obtenus[j].first) != nullptr)
                    {
                        Bonus* bonus_obtenu = dynamic_cast<Bonus*>(this->bonus_malus_obtenus[j].first);
                        if((malus->sorte_malus == PETITE_PLATEFORME && bonus_obtenu->sorte_bonus == GRANDE_PLATEFORME) //la plateforme était petite. Au lieu de lui donner sa taille normale, elle devient grande
                        || (malus->sorte_malus == PETITE_BALLE && bonus_obtenu->sorte_bonus == GRANDE_BALLE)) //la balle était petite. Au lieu de lui donner sa taille normale, elle devient grande
                        {
                            this->bonus_malus_obtenus.erase(this->bonus_malus_obtenus.begin() + j);
                            effet_malus(malus, balle);
                        }
                    }
                }
                effet_malus(malus, balle);
                timer = SDL_GetTicks() + 10000; //10 secondes
            }
            this->bonus_malus_obtenus.push_back(std::make_pair(this->bonus_malus[i], timer));
            this->bonus_malus.erase(this->bonus_malus.begin() + i);
        }
    }
}



void EnJeu::collision_between_balls(std::unique_ptr<Balle> &balle, const long long unsigned i, SingletonSysteme* const sing_syst)
{
    for(long long unsigned int j = 0; j < this->balles.size(); j++)
    {
        if(i != j && test_collision(balle->position, this->balles[j]->position)) //i != j pour ne pas compter une collision entre la même balle
        {
            int ball_1_center_x = balle->position.x + balle->position.w / 2;
            int ball_1_center_y = balle->position.y + balle->position.h / 2;
            int ball_2_center_x = this->balles[j]->position.x + this->balles[j]->position.w / 2;
            int ball_2_center_y = this->balles[j]->position.y + this->balles[j]->position.h / 2;

            int delta_x = ball_1_center_x - ball_2_center_x;
            int delta_y = ball_1_center_y - ball_2_center_y;

            if (std::abs(delta_x) > std::abs(delta_y))
            {
                if ((delta_x > 0 && balle->velocity_x < 0) || (delta_x <= 0 && balle->velocity_x >= 0)) //Balle 1 à droite de balle 2 || Balle 1 à gauche de balle 2
                {
                    if ((balle->velocity_x < 0 && this->balles[j]->velocity_x < 0 && balle->velocity_x < this->balles[j]->velocity_x) || //balle i va plus vite que balle j
                        (balle->velocity_x >= 0 && this->balles[j]->velocity_x > 0 && balle->velocity_x > this->balles[j]->velocity_x)) //balle i va plus vite que balle j
                    {
                        this->balles[j]->velocity_x = balle->velocity_x;
                    }
                    else if ((balle->velocity_x < 0 && this->balles[j]->velocity_x > 0) || (balle->velocity_x >= 0 && this->balles[j]->velocity_x < 0)) //balle i va dans le sens inverse en x de la balle j
                    {
                        this->balles[j]->velocity_x *= -1;
                    }
                    else this->balles[j]->velocity_x = balle->velocity_x; //la balle j monte ou descend sans bouger en x
                    balle->velocity_x *= -1;
                }
            }
            else if (std::abs(delta_x) < std::abs(delta_y))
            {
                if ((delta_y > 0 && balle->velocity_y < 0) || (delta_y <= 0 && balle->velocity_y >= 0)) //Balle 1 en bas de balle 2 || Balle 1 en haut de balle 2
                {
                    if ((balle->velocity_y < 0 && this->balles[j]->velocity_y < 0 && balle->velocity_y > this->balles[j]->velocity_y) || //balle i va plus vite que balle j
                        (balle->velocity_y >= 0 && this->balles[j]->velocity_y > 0 && balle->velocity_y < this->balles[j]->velocity_y)) //balle i va plus vite que balle j
                    {
                        this->balles[j]->velocity_y = balle->velocity_y;
                    }
                    else if ((balle->velocity_y < 0 && this->balles[j]->velocity_y > 0) || (balle->velocity_y >= 0 && this->balles[j]->velocity_y < 0)) //balle i va dans le sens inverse en y de la balle j
                    {
                        this->balles[j]->velocity_y *= -1;
                    }
                    else this->balles[j]->velocity_y = balle->velocity_y; //la balle j va à gauche ou à droite sans bouger en y
                    balle->velocity_y *= -1;
                }
            }
            else
            {
                balle->velocity_y *= -1;
                balle->velocity_x *= -1;
            }
            play_sound_collision_ball_and_brick_or_plateform(sing_syst);
        }
    }
}


void EnJeu::retirer_bonus_malus(Objet* objet, const Uint32 timer, const int i)
{
    if(timer > 0 && SDL_TICKS_PASSED(SDL_GetTicks(), timer)) //si timer bonus écoulé
    {
        //annuler le bonus/malus
        if(dynamic_cast<Bonus*>(objet) != nullptr) //if bonus
        {
            Bonus* bonus = dynamic_cast<Bonus*>(objet);
            //retirer le bonus
            if(bonus->sorte_bonus == GRANDE_PLATEFORME)
            {
                this->joueur.set_size_normal();
                check_new_player_position();
            }
            else if(bonus->sorte_bonus == GRANDE_BALLE)
            {
                for(auto& balle : this->balles)
                {
                    if(balle->is_big()) //la balle est grande
                    {
                        balle->set_size_normal();
                    }
                }
            }
        }
        else if(dynamic_cast<Malus*>(objet) != nullptr) //if malus
        {
            Malus* malus = dynamic_cast<Malus*>(objet);
            //retirer le malus
            if(malus->sorte_malus == PETITE_PLATEFORME)
            {
                this->joueur.set_size_normal();
                check_new_player_position();
            }
            else if(malus->sorte_malus == PETITE_BALLE)
            {
                for(auto& balle : this->balles)
                {
                    if(balle->is_small()) //la balle est petite
                    {
                        balle->set_size_normal();
                    }
                }
            }
        }
        this->bonus_malus_obtenus.erase(this->bonus_malus_obtenus.begin() + i);
    }
}


void EnJeu::handle_ball(std::unique_ptr<Balle> &balle, const int i, SingletonSysteme* const sing_syst)
{
    if(balle->position.y <= zone.y + offset_zone) //balle tape le plafond
    {
        balle->position.y = zone.y + offset_zone;
        balle->velocity_y *= -1;
        play_sound_collision_ball_and_wall(sing_syst);
    }
    else if(balle->position.x <= zone.x + offset_zone || (balle->position.x + balle->position.w) >= zone.x + zone.w - offset_zone) //balle tape un coté
    {
        if(balle->position.x <= zone.x + offset_zone) //côté gauche
        {
            balle->position.x = zone.x + offset_zone;
            if(balle->velocity_x == 0) //empêcher la balle de se bloquer en x contre le mur
                balle->velocity_x += balle->SPEED;
            else balle->velocity_x *= -1;
        }
        else if((balle->position.x + balle->position.w) >= zone.x + zone.w - offset_zone) //côté droit
        {
            balle->position.x = zone.x + zone.w - offset_zone - balle->position.w;
            if(balle->velocity_x == 0) //empêcher la balle de se bloquer en x contre le mur
                balle->velocity_x -= balle->SPEED;
            else balle->velocity_x *= -1;
        }
        play_sound_collision_ball_and_wall(sing_syst);
    }
    else if(balle->position.y + balle->position.h >= zone.y + zone.h) //balle tombe tout en bas
    {
        this->nb_balles_restantes -= 1;

        if(balle->is_small()) //la balle était petite, donc avait le malus PETITE_BALLE => supprimer le malus
        {
            for(long long unsigned int j = 0; j < this->bonus_malus_obtenus.size(); j++)
            {
                if(dynamic_cast<Malus*>(this->bonus_malus_obtenus[j].first) != nullptr)
                {
                    Malus* malus_obtenu = dynamic_cast<Malus*>(this->bonus_malus_obtenus[j].first);
                    if(malus_obtenu->sorte_malus == PETITE_BALLE)
                    {
                        this->bonus_malus_obtenus.erase(this->bonus_malus_obtenus.begin() + j);
                        break;
                    }
                }
            }
        }
        else if(balle->is_big()) //la balle était grande, donc avait le bonus GROSSE_BALLE => supprimer le bonus
        {
            for(long long unsigned int j = 0; j < this->bonus_malus_obtenus.size(); j++)
            {
                if(dynamic_cast<Bonus*>(this->bonus_malus_obtenus[j].first) != nullptr)
                {
                    Bonus* bonus_obtenu = dynamic_cast<Bonus*>(this->bonus_malus_obtenus[j].first);
                    if(bonus_obtenu->sorte_bonus == GRANDE_BALLE)
                    {
                        this->bonus_malus_obtenus.erase(this->bonus_malus_obtenus.begin() + j);
                        break;
                    }
                }
            }
        }
        this->balles.erase(this->balles.begin() + i);

        if(this->nb_balles_restantes == 0)
        {
            this->nb_essais_restants -= 1;
            if(this->nb_essais_restants > 0)
            {
                this->balles.emplace_back(std::make_unique<Balle>(sing_syst)); //balle de début
                this->nb_balles_restantes += 1;
            }
            else
            {
                //perdu!
                load_level(this->niveau_actuel, sing_syst);
                sing_syst->etat = MENU_PERDU;
            }
        }
    }
}


void EnJeu::draw(SDL_Renderer* const rendu)
{
    CHK(SDL_RenderCopy(rendu, this->texture_fond->get_texture(), nullptr, &fond), SDL_GetError());
    this->joueur.draw(rendu);

    for(auto& balle : this->balles)
    {
        balle->draw(rendu);
    }

    this->grille->draw(rendu);

    for(auto bonus_malus : this->bonus_malus)
    {
        bonus_malus->draw(rendu);
    }

    CHK(SDL_RenderCopy(rendu, this->texture_zone->get_texture(), nullptr, &zone), SDL_GetError());
    this->texte_nb_points_total.draw(rendu);
    this->texte_niveau_actuel.draw(rendu);

    //afficher le nombre d'essais restants, représenté par des images de balles
    if(this->nb_essais_restants >= 1)
    {
        SDL_Rect position = {50, 650, 30, 30};
        CHK(SDL_RenderCopy(rendu, this->texture_balle_nombre_de_vie->get_texture(), nullptr, &position), SDL_GetError());
        if(this->nb_essais_restants >= 2)
        {
            position.x += position.w + 1;
            CHK(SDL_RenderCopy(rendu, this->texture_balle_nombre_de_vie->get_texture(), nullptr, &position), SDL_GetError());
            if(this->nb_essais_restants == 3)
            {
                position.x += position.w + 1;
                CHK(SDL_RenderCopy(rendu, this->texture_balle_nombre_de_vie->get_texture(), nullptr, &position), SDL_GetError());
            }
        }
    }
}


void EnJeu::update(SingletonSysteme* const sing_syst)
{
    this->joueur.update(sing_syst);

    check_new_player_position(); //s'assurer que la plateforme ne sorte pas de la zone

    this->grille->update(sing_syst);

    for(long long unsigned int i = 0; i < this->bonus_malus.size(); i++)
    {
        this->bonus_malus[i]->update();
        if(this->bonus_malus[i]->position.y + this->bonus_malus[i]->position.h >= zone.y + zone.h) //bonus sous le terrain => le retirer du vector
        {
            this->bonus_malus.erase(this->bonus_malus.begin() + i);
        }
    }

    for(long long unsigned int i = 0; i < this->bonus_malus_obtenus.size(); i++)
    {
        retirer_bonus_malus(this->bonus_malus_obtenus[i].first, this->bonus_malus_obtenus[i].second, i);
    }

    for(long long unsigned int i = 0; i < this->balles.size(); i++) //boucle 1 : deux boucles différentes car suppression d'une balle dans handleBall !
    {
        this->balles[i]->update();
        handle_ball(this->balles[i], i, sing_syst);
    }
    for(long long unsigned int i = 0; i < this->balles.size(); i++) //boucle 2
    {
        collision_between_balls(this->balles[i], i, sing_syst);
        collision_ball_and_plateform(this->balles[i], sing_syst);
        collision_ball_and_brick(this->balles[i], sing_syst);
        collision_object_and_plateform(this->balles[i], sing_syst);
    }


    if(this->grille->tuiles.empty() == true)
    {
        this->nb_points_total += this->nb_essais_restants * 50000; //ajouter 50000 points par essai restant
        sing_syst->points_obtenus = this->nb_points_total;
        this->niveau_actuel += 1;
        load_level(this->niveau_actuel, sing_syst);

        if(this->niveau_actuel == 2 || this->niveau_actuel == 3 /*|| this->niveau_actuel == 4*/)
        {
            sing_syst->etat = MENU_FIN_NIVEAU;
        }
        else if(/*this->niveau_actuel == 5*/ this->niveau_actuel == 4)
        {
            sing_syst->etat = MENU_JEU_TERMINE;
        }
    }
}


void EnJeu::handle_events(const SDL_Event e, SingletonSysteme* const sing_syst)
{
    this->joueur.handle_events(e, sing_syst);
}
