#include "singleton_systeme.hpp"

//initialise les librairies (SDL2, SDL_TTF, SDL_Mixer, SDL_IMG), créer la fenêtre et le rendu, met l'état du jeu en MENU_PRINCIPAL
void SingletonSysteme::init(void)
{
    this->etat = MENU_PRINCIPAL;
    this->mode_deplacement = SOURIS;
    this->son_active = true;
    this->points_obtenus = 0;
    this->type_deplacement = CLASSIQUE;

    Uint32 flags;
    if(mode_fenetre == PLEIN_ECRAN)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    else if(mode_fenetre == FENETRE)
    {
        flags = SDL_WINDOW_RESIZABLE;
    }

    CHK(SDL_Init(SDL_INIT_VIDEO), SDL_GetError());
    CHK(TTF_Init(), TTF_GetError());
    CHK(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG), IMG_GetError());
    CHK(Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG), Mix_GetError());
    CHK(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_CHANNELS, 1024), Mix_GetError());

    this->window = new Window{"Brick Breaker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->LONGUEUR_FENETRE, this->HAUTEUR_FENETRE, flags};
    this->renderer = new Renderer{this->window->get_window(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC};

    CHK(SDL_RenderSetLogicalSize(this->renderer->get_renderer(), this->LONGUEUR_FENETRE, this->HAUTEUR_FENETRE), SDL_GetError());

    NCHK(this->son_collision_ball_and_brick_or_plateform = Mix_LoadWAV("./sound/brique.ogg"), Mix_GetError());
    NCHK(this->son_collision_ball_and_wall = Mix_LoadWAV("./sound/mur.ogg"), Mix_GetError());
    NCHK(this->son_brick_explosion = Mix_LoadWAV("./sound/brick_explosion.wav"), Mix_GetError());
    NCHK(this->son_bonus_malus = Mix_LoadWAV("./sound/bonus_malus.wav"), Mix_GetError());

    std::random_device dev;
    this->e = std::mt19937{dev()};
}


//nettoyage
void SingletonSysteme::destroy(void) const
{
    Mix_FreeChunk(son_collision_ball_and_brick_or_plateform);
    Mix_FreeChunk(son_brick_explosion);
    Mix_FreeChunk(son_collision_ball_and_wall);
    Mix_FreeChunk(son_bonus_malus);
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
