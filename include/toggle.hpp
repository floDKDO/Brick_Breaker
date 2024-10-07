#ifndef __TOGGLE__HPP__
#define __TOGGLE__HPP__

#include "selectionnable.hpp"
#include "texte.hpp"
#include "singleton_systeme.hpp"


class Toggle : public Selectionnable
{
    public:
        Toggle(const std::string image_bouton, const std::string image_texte, const SDL_Rect position, eventFunction func_ptr, const bool is_checked, SDL_Renderer* const rendu);
        virtual ~Toggle();

        void draw(SDL_Renderer* const rendu) override;
        void handle_events(SDL_Event e, SingletonSysteme* const sing_syst);
        bool collision(SDL_Rect dest, int x, int y) const override;
        void on_pointer_enter(SDL_Event e, SingletonSysteme* const sing_syst) override;
        void on_pointer_exit(SDL_Event e, SingletonSysteme* const sing_syst) override;
        void on_pointer_down(SDL_Event e, SingletonSysteme* const sing_syst) override;
        void on_click(SDL_Event e, SingletonSysteme* const sing_syst) override;
        void on_key_pressed(SDL_Event e, SingletonSysteme* const sing_syst) override;
        void on_key_released(SDL_Event e, SingletonSysteme* const sing_syst) override;
        void set_selected_if_move(Selectionnable* select_on_up, Selectionnable* select_on_down, Selectionnable* select_on_left, Selectionnable* select_on_right) override;
        void set_selected(Selectionnable* ui) override;
        void set_unselected(Selectionnable* previous) override;
        void select_new(Selectionnable* ui, SingletonSysteme* const sing_syst) override;

    protected:

    private:
        SDL_Rect position_texte;
        bool is_checked; //toggle coché ou non ?
        std::unique_ptr<Texture> image_toggle;
        std::unique_ptr<Texture> image_texte;
        std::unique_ptr<Texture> image_checked;
        std::unique_ptr<Texture> filtre_toggle_clicked;
        std::unique_ptr<Texture> filtre_toggle_hovered;
};

#endif // __TOGGLE__HPP__
