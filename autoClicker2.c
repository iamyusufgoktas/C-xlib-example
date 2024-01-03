#include <stdio.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

/// todo
/// make mouse clicked
/// get keyboard inputs
/// ctrl s -> stop
/// shift s -> start


int main() {
    Display *display;
    Window root;
    XEvent event;

    display = XOpenDisplay(nullptr);
    if (!display) {
        printf("Failed to open display\n");
        return 1;
    }

    root = DefaultRootWindow(display);

    // Simulate button press and release events repeatedly
    while (1) {
        // Press left button
        XTestFakeButtonEvent(display, Button1, True, CurrentTime);
        XFlush(display);
        usleep(100000); // Sleep for 100ms

        // Release left button
        XTestFakeButtonEvent(display, Button1, False, CurrentTime);
        XFlush(display);
        usleep(100000); // Sleep for 100ms
    }

    XCloseDisplay(display);

    return 0;
}
