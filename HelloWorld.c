#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h> // xlib stuff
#include <X11/Xutil.h>
#include <string.h>

int main()
{
    ///////logical display vars
    Display* display;
    int screen;
    Window root; // empty windows
    GC gc; // graphic content draw stuff

    ////// Window vars;
    Window window;
    Visual* visual = CopyFromParent; ///0L	/* border pixmap in CreateWindow
    int x,y, width, height;

    char * message = " Hello World!";

    int done = 0; // events
    XEvent event;

    /// window server
    display = XOpenDisplay((char*) NULL); // open display
    if(display == (Display*) NULL)
    {
        fprintf(stderr, "Cant connect server %s",XDisplayName((char*) NULL));
        exit(1);
    }
    // in theory we re in x server
    screen = DefaultScreen(display); // return index of default screen
    root = RootWindow(display,screen); // return id of root window
    gc = DefaultGC(display,screen); // return defaults graphic context of the screen

    // server control
    fprintf(stderr, "Display string %s \n", DisplayString(display));
    fprintf(stderr, "Index %d \n", DefaultScreen(display));
    fprintf(stderr, "Weight %d \n", DisplayWidth(display,screen));
    fprintf(stderr, "Height %d \n", DisplayHeight(display,screen));

    // subscribe to events (Exposure, ButtonPress, and KeyPress), set bg and fg pixels
    // and change window attributes
    XSetWindowAttributes attributes; // change window attributes
    unsigned long attribute_mask = CWEventMask | CWBackPixel | CWBorderPixel;
    unsigned long event_mask = ExposureMask | ButtonPressMask | KeyPressMask;

    int border_width = 2;
    x = y = 150;
    width = 500;
    height = 100;
    attributes.event_mask = event_mask;
    attributes.border_pixel = BlackPixel(display, screen),
    attributes.background_pixel = WhitePixel(display, screen);

    window = XCreateWindow( display, root, x, y, width, height,
                            border_width, CopyFromParent, InputOutput,
                            visual, attribute_mask, &attributes);
    char *window_name = "Hello World";
    char *application_class = "example_class";

    // add name
    XClassHint class_hints;
    class_hints.res_class = application_class;
    class_hints.res_name = window_name;

    XStoreName(display, window, window_name);
    XSetClassHint(display, window, &class_hints);

    // Display Window

    XMapRaised(display, window); // maps allws it to be drawn
    XFlush(display); // to flush

    char msg[1024] = "";
    char key[32];

    // Event loop
    while(1) {
        // Get next event from queue
        XEvent event;
        XNextEvent(display, &event);

        // Keyboard
        if (event.type == KeyPress) {
            int len = XLookupString(&event.xkey, key, sizeof(key) - 1, 0, 0);
            key[len] = 0;
            printf("Key %s pressed\n",key);
            strcat(msg, key);

        }
        else if(event.type == ButtonPress) {
            printf("Button pressed\n");
        }
        // Refresh
        if (event.type == KeyPress || event.type == Expose) {
            XClearWindow(display, window);
            XDrawString(display, window, gc, 10, 20, msg, strlen(msg));
        }

    }

    // free structures
    XCloseDisplay(display);



}


