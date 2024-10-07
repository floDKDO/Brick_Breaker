#ifndef __SELECTIONNABLE__HPP__
#define __SELECTIONNABLE__HPP__

#include "singleton_systeme.hpp"

//état d'un bouton ou toggle
enum etat
{
    NORMAL,
    HOVERED,
    CLICKED,
    SELECTED
};

//classe mere virtuelle (pour polymorphisme) de Toggle et Bouton
class Selectionnable
{
    public:
        Selectionnable(){}
        virtual ~Selectionnable(){}

        SDL_Rect position;
        etat etat;

        virtual void draw(SDL_Renderer* const rendu) = 0;
        virtual void handle_events(SDL_Event e, SingletonSysteme* const sing_syst);
        virtual bool collision(SDL_Rect dest, int x, int y) const;
        virtual void on_pointer_enter(SDL_Event e, SingletonSysteme* const sing_syst);
        virtual void on_pointer_exit(SDL_Event e, SingletonSysteme* const sing_syst);
        virtual void on_pointer_down(SDL_Event e, SingletonSysteme* const sing_syst);
        virtual void on_click(SDL_Event e, SingletonSysteme* const sing_syst) = 0;
        virtual void on_key_pressed(SDL_Event e, SingletonSysteme* const sing_syst) = 0;
        virtual void on_key_released(SDL_Event e, SingletonSysteme* const sing_syst);
        virtual void set_selected_if_move(Selectionnable* select_on_up, Selectionnable* select_on_down, Selectionnable* select_on_left, Selectionnable* select_on_right);
        virtual void set_selected(Selectionnable* ui);
        virtual void set_unselected(Selectionnable* previous);
        virtual void select_new(Selectionnable* ui, SingletonSysteme* const sing_syst);

    protected:

        bool son_joue;
        Mix_Chunk* hover_sound;
        Mix_Chunk* click_sound;
        int previous_etat;
        bool clic_avant_collision;

        typedef void(*eventFunction)(SingletonSysteme*, Selectionnable*);
        eventFunction func_ptr; //pointeur sur la fonction qui sera lancée quand il y aura un clic sur le selectionnable

        //ui à sélectionner selon la touche de déplacement appuyée
        Selectionnable* select_on_up;
        Selectionnable* select_on_down;
        Selectionnable* select_on_left;
        Selectionnable* select_on_right;
        static bool verrou; //pour empecher le double defilement (passer d'un ui à deux autres en un appuie)

    private:
};

#endif // __SELECTIONNABLE__HPP__
