#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <signal.h>

// Global flag to keep track of whether the autoclicker is running or not
int isRunning = 1;

// Function to handle the SIGINT signal (Ctrl+C)
void handleSigInt(int sig)
{
    isRunning = 0;
    printf("\nAutoclicker stopped.\n");
    exit(0); // Terminate the program
}

int main()
{
    // Register the SIGINT signal handler
    //In this version, the handleSigInt function is registered as the signal handler for SIGINT, and it calls exit(0) to terminate the program when the signal is received.
    signal(SIGINT, handleSigInt);

    printf("Autoclicker using Xlib for Linux (Press Ctrl+C to stop)\n");

    // Open the display
    Display *display = XOpenDisplay(NULL);
    if (!display)
    {
        printf("Unable to open display.\n");
        return 1;
    }

    // Autoclicker loop
    while (isRunning)
    {
        // Generate random click delay between 100ms and 500ms
        int clickDelayMs = (rand() % 400) + 100;

        // Print click delay for debugging
        // printf("Click delay: %d ms\n", clickDelayMs);

        // Sleep for the click delay
        usleep(clickDelayMs * 1000);

        // Create a button press and release event for the left mouse button
        XTestFakeButtonEvent(display, Button1, True, CurrentTime);
        XTestFakeButtonEvent(display, Button1, False, CurrentTime);

        // Flush the Xlib event queue
        XFlush(display);
    }

    // Close the display
    XCloseDisplay(display);

    return 0;
}
