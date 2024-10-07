#include "window.hpp"

//Classe qui encapsule SDL_Window
Window::Window(const std::string titre, const int x, const int y, const int w, const int h, const Uint32 flags)
:titre(titre), x(x), y(y), w(w), h(h), flags(flags)
{
    if((this->fenetre = SDL_CreateWindow(titre.c_str(), x, y, w, h, flags)) == nullptr)
    {
        std::cerr << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
}


Window::~Window()
{
    if(this->fenetre != nullptr)
    {
        SDL_DestroyWindow(this->fenetre);
        this->fenetre = nullptr;
    }
}


SDL_Window* const& Window::get_window() const
{
    return this->fenetre;
}
