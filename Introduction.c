#include <X11/Xlib.h>
#include <unistd.h>

int main()
{
    Display  * display = XOpenDisplay(NULL);
    if(display)
    {
        // Create the window
        Window windows = XCreateWindow(display, DefaultRootWindow(display), 0, 0, 200,
                                 100, 0, CopyFromParent, CopyFromParent,
                                 CopyFromParent, 0, 0);
        XMapWindow(display,windows);
        XFlush(display);
        sleep(10); // while for it
    }

}
