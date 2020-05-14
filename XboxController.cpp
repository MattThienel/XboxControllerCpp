#include "XboxController.h"

XboxController::XboxController() {
    this->device = "/dev/input/js0";
    initializeController();
}

XboxController::XboxController(const char *device) {
    this->device = device;
    initializeController();
}

double XboxController::getXAxis(Hand hand) {
    if(hand == Hand::left) {
        if(event.type == JS_EVENT_AXIS && static_cast<unsigned>(event.number) == 0) {
            xAxis[0] = event.value/32767.0;
        }
        return xAxis[0];
    } else {
        if(event.type == JS_EVENT_AXIS && static_cast<unsigned>(event.number) == 3) {
            xAxis[1] = event.value/32767.0;
        }
        return xAxis[1];
    }
    return -1;
}

double XboxController::getYAxis(Hand hand) {
    if(hand == Hand::left) {
        if(event.type == JS_EVENT_AXIS && static_cast<unsigned>(event.number) == 1) {
            yAxis[0] = event.value/-32767.0;
        }
        return yAxis[0];
    } else {
        if(event.type == JS_EVENT_AXIS && static_cast<unsigned>(event.number) == 4) {
            yAxis[1] = event.value/-32767.0;
        }
        return yAxis[1];
    }
    return 0;
}

bool XboxController::getBumper(Hand hand) {
    if(hand == Hand::left) {
        return genericButtonPoll(XboxButtons::leftBumper);
    } else {
        return genericButtonPoll(XboxButtons::rightBumper);
    }
}

bool XboxController::getStickButton(Hand hand) {
    if(hand == Hand::left) {
        return genericButtonPoll(XboxButtons::leftStick);
    } else {
        return genericButtonPoll(XboxButtons::rightStick);
    }
}

double XboxController::getTrigger(Hand hand) {
    if(hand == Hand::left) {
        if(event.type == JS_EVENT_AXIS && static_cast<unsigned>(event.number) == 2) {
            triggerAxis[0] = ((event.value/32767.0) + 1.0)/2.0;
        }
        return triggerAxis[0];
    } else {
        if(event.type == JS_EVENT_AXIS && static_cast<unsigned>(event.number) == 5) {
            triggerAxis[1] = ((event.value/32767.0) + 1.0)/2.0;
        }
        return triggerAxis[1];
    }
    return 0;
}

int XboxController::getDPadX() {
    if(event.type == JS_EVENT_AXIS) {
        if(event.number == 6) {
            return event.value/32767;
        }
    }
    return 0;
}

int XboxController::getDPadY() {
    if(event.type == JS_EVENT_AXIS) {
        if(event.number == 7) {
            return event.value/-32767;
        }
    }
    return 0;
}

void XboxController::initializeController() {
    js = open(device, O_RDONLY);
    if(js == -1) {
        char str[80];
        strcpy(str, "Could not open controller at ");
        strcat(str, device);
        perror(str);
    }

    if (ioctl(js, JSIOCGNAME(sizeof(name)), name) < 0) {
        strncpy(name, "Unknown", sizeof(name)); 
    }
    char numAxes;
    char numButtons;
    ioctl(js, JSIOCGAXES, &numAxes);
    ioctl(js, JSIOCGBUTTONS, &numButtons);
    ioctl(js, JSIOCGVERSION, &driverVersion);
    numberOfAxes = static_cast<int>(numAxes);
    numberOfButtons = static_cast<int>(numButtons);
}

bool XboxController::isConnected() {
    ssize_t bytes = read(js, &event, sizeof(event));
    if(bytes == sizeof(event)) {
        return true;
    }
    return false;
}

bool XboxController::genericButtonPoll(XboxButtons button) {
    int buttonNumber = static_cast<int>(button);
    if(event.type == JS_EVENT_BUTTON && static_cast<unsigned>(event.number) == buttonNumber) {
        buttonStates[buttonNumber] = event.value;
        return event.value;
    }
    return buttonStates[buttonNumber];
}