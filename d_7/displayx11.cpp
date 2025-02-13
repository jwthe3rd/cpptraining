#include <iostream>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>


using namespace std;

int main()
{

    int windowPositionX = 100;
    int windowPositionY = 100;
    int windowWidth = 500;
    int windowHeight = 300;
    int windowBorderWidth = 1;

    Display* display = XOpenDisplay(NULL);

    if (display == NULL)
    {
        return 1;
    }

    int screen = DefaultScreen(display);

    Window win = XCreateSimpleWindow(display, RootWindow(display, screen),
                                     windowPositionX,windowPositionY,windowWidth,windowHeight,windowBorderWidth,
                                     BlackPixel(display, screen), // Border color 
                                     WhitePixel(display, screen)); // Background Colow

    XSelectInput(display, win, ExposureMask | KeyPressMask);
    XMapWindow(display, win);

    GC gc = XCreateGC(display, win, 0, NULL);
    XSetForeground(display, gc, BlackPixel(display, screen));

    srand(time(0));

    XEvent event;
    bool running = true;

    while (running)
    {
        XNextEvent(display, &event);

        if (event.type == KeyPress)
        {
            KeySym keysym = XLookupKeysym(&event.xkey, 0);


            if (keysym == XK_Return)
            {
                running = false;
            }

            else if (keysym == XK_n)
            {
                int x = rand() % 500;
                int y = rand() % 300;
                int radius = 10;  // Fixed radius

                XSetForeground(display, gc, 0x00FF00); // Green color
                XFillArc(display, win, gc, x - radius, y - radius, radius * 2, radius * 2, 0, 360 * 64);
                XFlush(display);
            }
        }
    }
    

    XFreeGC(display, gc);
    XDestroyWindow(display, win);
    XCloseDisplay(display);
    return 0;
}