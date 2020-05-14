#ifndef XBOXCONTROLLER
#define XBOXCONTROLLER

#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <iostream>
#include <cstring>

using namespace std;

/**
 * Specifies which side of the controller to use for input with left and right
 * ie. left joystick and right joystick
 */
enum Hand {
    left, right
};

class XboxController {
public:

    XboxController(); // Default constructor for controller at /dev/input/js0
    XboxController(const char *device); // Constructor for controller at another location
    ~XboxController() {close(js);}; // Close controller 
    
    double getXAxis(Hand hand); // Returns the x value of joystick: 1 right, -1 left
    double getYAxis(Hand hand); // Returns the y value of joystick: 1 up, -1 down
    double getTrigger(Hand hand); // Returns value of trigger: 0 when released, 1 when pressed
    int getDPadX(); // Returns value of dpad on the x axis: 1 right, 0 not pressed, -1 left
    int getDPadY(); // Returns value of dpad on the y axis: 1 up, 0 not pressed, -1 down
    bool isConnected(); // Returns true when the controller is connected, false when disconnected

    /**
     * Returns current value of button
     * true if pressed 
     * false if not pressed
     */
    bool getAButton() {return genericButtonPoll(XboxButtons::a);};
    bool getBButton() {return genericButtonPoll(XboxButtons::b);};
    bool getXButton() {return genericButtonPoll(XboxButtons::x);};
    bool getYButton() {return genericButtonPoll(XboxButtons::y);};
    bool getBumper(Hand hand);
    bool getStickButton(Hand hand);
    bool getViewButton() {return genericButtonPoll(XboxButtons::view);};
    bool getMenuButton() {return genericButtonPoll(XboxButtons::menu);};

    unsigned char getEventType() {return event.type;} // Returns the event type: ie. JS_EVENT_INIT/JS_EVENT_AXIS, JS_EVENT_BUTTON
    __u32 getEventTime() {return event.time;}; // Returns the event time in milliseconds

    char name[80]; // Name of controller
    int numberOfButtons;
    int numberOfAxes;
    int driverVersion;
    
private:
    /**
     *  Stores the id for buttons
     */
    enum XboxButtons {
        a,b,x,y,leftBumper,rightBumper,view,menu,leftStick,rightStick
    };

    const char *device;
    int js;
    struct js_event event;

    /**
     * Stores the current value of buttons and axes
     */
    bool buttonStates[10] = {0}; // a,b,x,y,leftBumper,rightBumper,view,menu,leftStick,rightStick
    double triggerAxis[2] = {0}; // leftTrigger,rightTrigger
    double xAxis[2] = {0}; // leftAxis,rightAxis
    double yAxis[2] = {0}; // leftAxis,rightAxis

    void initializeController(); // Initializes device
    bool genericButtonPoll(XboxButtons button); // Generic function to poll buttons
};

#endif