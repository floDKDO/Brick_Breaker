#include "singleton_systeme.hpp"
#include "bouton.hpp"
#include "texte.hpp"
#include "joueur.hpp"
#include "toggle.hpp"
#include "menuPrincipal.hpp"
#include "menuOptions.hpp"
#include "menuFinNiveau.hpp"
#include "menuPerdu.hpp"
#include "menuJeuTermine.hpp"
#include "tuile.hpp"
#include "enJeu.hpp"


int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    SingletonSysteme::instance().init();

    SDL_Renderer* rendu = SingletonSysteme::instance().renderer->get_renderer();
    SingletonSysteme* const sing_syst = &SingletonSysteme::instance();

    MenuPrincipal menuPrincipal{sing_syst};
    MenuOptions menuOptions{sing_syst};
    EnJeu enJeu{sing_syst};
    MenuFinNiveau menuFinNiveau{sing_syst};
    MenuPerdu menuPerdu{sing_syst};
    MenuJeuTermine menuJeuTermine{sing_syst};

    bool quitter = false;
    while(quitter == false)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e) != 0)
        {
            switch(e.type)
            {
                case SDL_WINDOWEVENT:

                    if(e.window.event == SDL_WINDOWEVENT_CLOSE)
                    {
                        quitter = true;
                    }
                    break;

                case SDL_KEYDOWN:

                    if(e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        quitter = true;
                    }
                    break;

                default :
                    break;
            }

            if(sing_syst->etat == MENU_PRINCIPAL)
            {
                menuPrincipal.handle_events(e, sing_syst);
            }
            else if(sing_syst->etat == MENU_OPTIONS)
            {
                menuOptions.handle_events(e, sing_syst);
            }
            else if(sing_syst->etat == EN_JEU)
            {
                enJeu.handle_events(e, sing_syst);
            }
            else if(sing_syst->etat == MENU_FIN_NIVEAU)
            {
                menuFinNiveau.handle_events(e, sing_syst);
            }
            else if(sing_syst->etat == MENU_PERDU)
            {
                menuPerdu.handle_events(e, sing_syst);
            }
            else if(sing_syst->etat == MENU_JEU_TERMINE)
            {
                menuJeuTermine.handle_events(e, sing_syst);
            }
        }

        CHK(SDL_SetRenderDrawColor(rendu, 0, 0, 130, 255), SDL_GetError());
        CHK(SDL_RenderClear(rendu), SDL_GetError());

        if(sing_syst->etat == MENU_PRINCIPAL)
        {
            menuPrincipal.draw(rendu, sing_syst);
        }
        else if(sing_syst->etat == MENU_OPTIONS)
        {
            menuOptions.draw(rendu, sing_syst);
        }
        else if(sing_syst->etat == EN_JEU)
        {
            enJeu.draw(rendu);
            enJeu.update(sing_syst);
        }
        else if(sing_syst->etat == MENU_FIN_NIVEAU)
        {
            menuFinNiveau.draw(rendu, sing_syst);
        }
        else if(sing_syst->etat == MENU_PERDU)
        {
            menuPerdu.draw(rendu, sing_syst);
        }
        else if(sing_syst->etat == MENU_JEU_TERMINE)
        {
            menuJeuTermine.draw(rendu, sing_syst);
        }

        SDL_RenderPresent(rendu);
        SDL_Delay(16); //limiter la boucle de jeu à 60 FPS
    }
    sing_syst->destroy();
    return EXIT_SUCCESS;
}
