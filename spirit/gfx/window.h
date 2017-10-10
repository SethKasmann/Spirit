#ifndef WINDOW_H
#define WINDOW_H

struct SDL_Window;
union SDL_Event;
typedef void* SDL_GLContext;

namespace spirit {

    class Window
    {
    private:
        static int event_watch_callback(void* userdata, SDL_Event* event); 
    public:
        Window(const char* name, int w, int h);
        ~Window();
        bool closed() const;
        void set_closed(int closed);
        void resize();
        void clear();
        void update();
        void mouse_position(int* x, int* y) const;
        int get_w() const;
        int get_h() const;
    private:
        bool _closed;
        SDL_Window* _window;
        SDL_GLContext _context;
        static Window* _self;
    };

}

#endif