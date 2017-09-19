#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "window.h"

namespace spirit {

    // Initialize self ptr to null.
    Window* Window::_self = nullptr;

    Window::Window(const char* name, int w, int h)
    : _closed(false)
    , _window(nullptr)
    , _context(nullptr)
    {

        _self = this;
        // Initialize SDL.
        // ----- TODO: move this into a static obj ----- //
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cout << "SDL failed to initialize video.\n";
        }

        // Create SDL window.
        _window = SDL_CreateWindow(
            name,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            w,
            h,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

        // Check the window was created propertly.
        if (_window == nullptr)
        {
            std::cout << "Failed to create window.\n";
        }

        // Set profile mask so old versions cannot be used.
        // ----- TODO: is this really necessary ----- //
        // Causes GLEW to fail to initialize... ?
        // Set GL version.
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        //SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                            //SDL_GL_CONTEXT_PROFILE_CORE);


        // Set GL double buffering.
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        // Create OpenGL rendering contect to connect to the window.
        _context = SDL_GL_CreateContext(_window);

        // Make context current required before initializing GLEW.
        if (SDL_GL_MakeCurrent(_window, _context))
        {
            std::cout << "Failed to set up context for window.\n";
        }

        // Initialize GLEW.
        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (err != GLEW_OK)
        {
            std::cout << "GLEW failed to initialize.\n";
        }

        // Set SDL event callback.
        SDL_AddEventWatch(event_watch_callback, NULL);

    }

    Window::~Window()
    {
        // Delete the event callback.
        // ----- TODO: Will not work with multi window ----- //
        SDL_DelEventWatch(event_watch_callback, NULL);

        // Set _self ptr to null. No other cleanup needed here.
        if (_self)
        {   
            _self = nullptr;
        }

        // Destroy context.
        if (_context)
        {
            SDL_GL_DeleteContext(_context); 
        }

        // Destroy window.
        if (_window)
        {
            SDL_DestroyWindow(_window);
        }

        SDL_Quit();

    }

    bool Window::closed() const
    {
        return _closed;
    }

    // Set the private closed variable. This function is necessary
    // since closed may be changed from the event_watch, which is
    // a static function (since it's a callback).
    void Window::set_closed(int closed)
    {
        _closed = closed;
    }

    // Resize the window and maintain the aspect ratio.
    void Window::resize()
    {
        int w, h;
        SDL_GetWindowSize(_window, &w, &h);
        glViewport(0, 0, w, h);
    }

    // Clear the window. Should be called at the beginning of the
    // game loop.
    void Window::clear()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    // Event watch function. This callback run whenever a SDL_Event
    // is added to the event queue. We can use the data from events
    // to update the window.
    int Window::event_watch_callback(void* userdata, SDL_Event* event)
    {
        switch (event->type)
        {
            case SDL_QUIT:
            {
                _self->set_closed(true);
                break;
            }
            case SDL_WINDOWEVENT:
            {
                if (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    _self->resize();
                }
                else if (event->window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    _self->set_closed(true);
                }
                break;
            }
        }
        return true;
    }

    // Swap the GL buffer.
    void Window::update()
    {
        SDL_Event e;
        SDL_PumpEvents();
        SDL_GL_SwapWindow(_window);
    }

}
