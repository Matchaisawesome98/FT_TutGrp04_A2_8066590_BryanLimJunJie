#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>
#include <iomanip>

#include "ShapeTwoD.h"
// #include "Square.h"
#include "Circle.h"
// #include "Rectangle.h"
// #include "Cross.h"

using namespace std;

class MenuSystem {
private:
    vector<ShapeTwoD*> shapes; // Store all shapes

public:
    ~MenuSystem() {
        // Clean up dynamically allocated shapes
        for (auto shape : shapes) {
            delete shape;
        }
    }
    void displayMenu(){
        cout << "Student ID: 8066590" << endl;
        cout << "Student Name: Bryan Lim Jun Jie" << endl;
        cout << "-------------------------------" << endl;
        cout << "Welcome to Assn2 program!" << endl;
        cout << "\n1)\tInput sensor data" << endl;
        cout << "2)\tCompute area (for all records)" << endl;
        cout << "3)\tPrint shapes report" << endl;
        cout << "4)\tSort shape data" << endl;
        cout << "Please enter choice: ";
    }
    int getUserChoice() {
        int choice;
        cin >> choice;
        cin.ignore();
        cout << endl;
        return choice;
    }
    void inputSensorData() {
        cout << "[ Input sensor data ]" << endl;
        cout << "Please enter name of shape: ";
        string shapeName;
        cin >> shapeName;
        cin.ignore();

        if (shapeName == "Circle") {
            cout << "Please enter special type: ";
            string specialType;
            cin >> specialType;
            cin.ignore();

            bool isWarpSpace = (specialType == "WS");

            cout << "Please enter x-ordinate of center: ";
            int centerX;
            cin >> centerX;
            cin.ignore();

            cout << "Please enter y-ordinate of center: ";
            int centerY;
            cin >> centerY;
            cin.ignore();

            cout << "Please enter radius (units): ";
            int radius;
            cin >> radius;
            cin.ignore();

            // Create new circle and add to shapes vector
            Circle* newCircle = new Circle(shapeName, isWarpSpace);
            newCircle->setCenter(centerX, centerY);
            newCircle->setRadius(radius);

            shapes.push_back(newCircle);

            cout << "Record successfully stored. Going back to main menu ..." << endl;
        } else {
            cout << "Shape type '" << shapeName << "' is not supported yet." << endl;
        }
    }
    bool processMenuChoice(int choice) {
        switch (choice) {
            case 1:
                inputSensorData();
                break;
            case 2:
                cout << "Compute area (for all records)" << endl;
                break;
            case 3:
                cout << "Print shapes report" << endl;
                break;
            case 4:
                cout << "Sort shape data" << endl;
                break;
            default:
                cout << "Invalid choice! Please enter a number between 1 and 4." << endl;
                break;
        }
        return true;
    }
    void runMenu() {
        bool keepRunning = true;
        while (keepRunning) {
            displayMenu();
            int choice = getUserChoice();
            keepRunning = processMenuChoice(choice);
        }
    }
};


int main() {
    MenuSystem menu;
    menu.runMenu();
    return 0;
}