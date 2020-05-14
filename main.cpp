#include <iostream>
#include <stdlib.h>
#include "XboxController.h"

using namespace std;

#define CLEAR_SCREEN "\033[2J"

int main(int argc, char *argv[]) {

    /**
     * Default controller located at /dev/input/js0
     * For other cases add location of controller to constructor as string
     * ie. "/dev/input/js1"
     */

    XboxController controller("/dev/input/js0");

    while(controller.isConnected()) {
        cout << controller.name << endl;
        cout << "Driver Version: " << controller.driverVersion << endl;
        cout << "Event Time: " << controller.getEventTime() << endl;
        cout << "Left Joystick [X] " << controller.getXAxis(Hand::left) << " : [Y] " << controller.getYAxis(Hand::left) << " : [Pressed] " << controller.getStickButton(Hand::left) << endl;
        cout << "Right Joystick [X] " << controller.getXAxis(Hand::right) << " : [Y] " << controller.getYAxis(Hand::right) << " : [Pressed] " << controller.getStickButton(Hand::right) << endl;
        cout << "Buttons [A] " << controller.getAButton() << " : [B] " << controller.getBButton() << " : [X] " << controller.getXButton() << " : [Y] " << controller.getYButton() << endl;
        cout << "Bumpers [Left] " << controller.getBumper(Hand::left) << " : [Right] " << controller.getBumper(Hand::right) << endl;
        cout << "Triggers [Left] " << controller.getTrigger(Hand::left) << " : [Right] " << controller.getTrigger(Hand::right) << endl;
        cout << "DPad [Left/Right] " << controller.getDPadX() << " : [Up/Down] " << controller.getDPadY() << endl;
        cout << "View Button " << controller.getViewButton() << " : " << "Menu Button " << controller.getMenuButton() << flush << endl;
        cout << CLEAR_SCREEN;
    }
    

    return 0;
    
}