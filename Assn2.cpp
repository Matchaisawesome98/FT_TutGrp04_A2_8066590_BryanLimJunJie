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
public:
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
        return choice;
    }
    bool processMenuChoice(int choice) {
        switch (choice) {
            case 1:
                cout << "Input sensor data" << endl;
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
                return true;
        }
        return false;  // Return false to continue the menu loop
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
    menu.displayMenu();
    menu.runMenu();
    return 0;
}