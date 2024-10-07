#include "grille.hpp"

Grille::Grille(const std::string fichier_carte, SingletonSysteme* const sing_syst)
{
    if(sing_syst->type_deplacement == CLASSIQUE)
    {
        init_tuiles(fichier_carte, sing_syst);
    }
    else //mode CIRCULAIRE
    {
        Uint8 couleur = 0;
        const float circle_radius_brick = 200.0f; //rayon du cercle de brique
        for (int angle = 0; angle < 360; angle += 10)
        {
            //calcul de la position de chaque rectangle autour du cercle
            float angle_rad = angle * M_PI / 180.0f;
            int x = sing_syst->LONGUEUR_FENETRE/2 - 100/2 + int(circle_radius_brick * cos(angle_rad));
            int y = 640/2 + int(circle_radius_brick * sin(angle_rad));

            this->tuiles.emplace_back(new Tuile{{couleur, 0, 255, 255}, x, y});
            couleur += 20; //faire varier la couleur des tuiles sur le cercle
        }
    }
}


//charger les tuiles d'un fichier ASCII
void Grille::init_tuiles(const std::string fichier_carte, SingletonSysteme* const sing_syst)
{
    const int TILE_WIDTH = 53; //52 (taille tuile) + 1 pour avoir un écart entre les tuiles
    const int TILE_HEIGHT = 53;

    int x = sing_syst->X_OFFSET_ZONE, y = 0; //en x, la position des tuiles est au minimum de X_OFFSET_ZONE

    std::ifstream fichier;
    fichier.open(fichier_carte);

    if(fichier.fail())
    {
        std::cout << "Fail..." << std::endl;
		exit(EXIT_FAILURE);
    }

    std::string ligne;
    std::vector<std::string> tuiles_fichier;

    //lire le fichier ligne par ligne
    while(std::getline(fichier, ligne))
	{
        std::stringstream ss(ligne);
        std::string temp;

        //séparer la ligne en mots avec les espaces (un espace entre chaque mot) comme délimiteur
        while(std::getline(ss, temp, ' '))
        {
            tuiles_fichier.push_back(temp); //mettre les mots dans le tableau
        }

        //parcourir chaque mot du tableau => un mot est une tuile
        for(long long unsigned int i = 0; i < tuiles_fichier.size(); i++)
        {
            if(tuiles_fichier[i].find("00") != std::string::npos) //00 => pas de tuile, du vide
            {

            }
            else if(tuiles_fichier[i].find("01") != std::string::npos) //01
            {
                this->tuiles.emplace_back(std::make_unique<Tuile>("./img/brique_bleue.png", x, y, 1, sing_syst->e, sing_syst)); //1 pv
            }
            else if(tuiles_fichier[i].find("02") != std::string::npos) //02
            {
                this->tuiles.emplace_back(std::make_unique<Tuile>("./img/brique_verte.png", x, y, 1, sing_syst->e, sing_syst)); //1 pv
            }
            else if(tuiles_fichier[i].find("03") != std::string::npos) //03
            {
                this->tuiles.emplace_back(std::make_unique<Tuile>("./img/brique_orange.png", x, y, 1, sing_syst->e, sing_syst)); //1 pv
            }
            else if(tuiles_fichier[i].find("04") != std::string::npos) //04
            {
                this->tuiles.emplace_back(std::make_unique<Tuile>("./img/brique_jaune.png", x, y, 1, sing_syst->e, sing_syst)); //1 pv
            }
            else if(tuiles_fichier[i].find("05") != std::string::npos) //05
            {
                this->tuiles.emplace_back(std::make_unique<Tuile>("./img/brique_grise.png", x, y, 2, sing_syst->e, sing_syst)); //2 pv
            }
            else if(tuiles_fichier[i].find("06") != std::string::npos) //05
            {
                this->tuiles.emplace_back(std::make_unique<Tuile>("./img/brique_rouge.png", x, y, 3, sing_syst->e, sing_syst)); //3 pv
            }

            //prochaine tuile
            x += TILE_WIDTH;
        }

        //comme on change de ligne, alors on change le x à 0 (debut de ligne) et le y (+= hauteur tuile)
        x = sing_syst->X_OFFSET_ZONE;
        y += TILE_HEIGHT;

        //on vide le tableau de string car cette ligne est finie
        tuiles_fichier.clear();
	}
    fichier.close();
}


void Grille::draw(SDL_Renderer* const rendu)
{
    for(auto& tuile : this->tuiles)
    {
        tuile->draw(rendu);
    }
}


void Grille::update(SingletonSysteme* const sing_syst)
{
    for(auto& tuile : this->tuiles)
    {
        tuile->update(sing_syst);
    }
}
