#ifndef __WINDOW__HPP__
#define __WINDOW__HPP__

#include <SDL2/SDL.h>
#include <string>
#include <iostream>

//Classe qui encapsule SDL_Window
class Window
{
    public:
        Window(const std::string titre, const int x, const int y, const int w, const int h, const Uint32 flags);
        ~Window();
        SDL_Window* const& get_window() const;

    protected:

    private:
        SDL_Window* fenetre;
        std::string titre;
        int x, y, w, h;
        Uint32 flags;
};

#endif
