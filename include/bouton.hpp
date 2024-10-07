#ifndef __BOUTON__HPP__
#define __BOUTON__HPP__

#include "selectionnable.hpp"
#include "singleton_systeme.hpp"
#include <memory>

class Bouton : public Selectionnable
{
    public:

        Bouton(const std::string image_bouton, const std::string image_texte, const SDL_Rect position, eventFunction func_ptr, SDL_Renderer* const rendu);
        virtual ~Bouton();

        std::unique_ptr<Texture> image_texte;

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
        std::unique_ptr<Texture> image_bouton;
        std::unique_ptr<Texture> filtre_bouton_clicked;
        std::unique_ptr<Texture> filtre_bouton_hovered;
};

#endif // __BOUTON__HPP__
