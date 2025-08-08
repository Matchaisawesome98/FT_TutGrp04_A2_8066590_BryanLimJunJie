#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>
#include <iomanip>

#include "ShapeTwoD.h"
#include "Square.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Cross.h"

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

    void displayMenu() {
        cout << "Student ID: 8066590" << endl;
        cout << "Student Name: Bryan Lim Jun Jie" << endl;
        cout << "-------------------------------" << endl;
        cout << "Welcome to Assn2 program!" << endl;
        cout << endl;
        cout << "1)\tInput sensor data" << endl;
        cout << "2)\tCompute area (for all records)" << endl;
        cout << "3)\tPrint shapes report" << endl;
        cout << "4)\tSort shape data" << endl;
        cout << endl;
        cout << "Please enter your choice : ";
    }

    int getUserChoice() {
        int choice;
        cin >> choice;
        cin.ignore();
        return choice;
    }

    void inputSensorData() {
        cout << "[ Input sensor data ]" << endl;
        cout << "Please enter name of shape : ";
        string shapeName;
        cin >> shapeName;
        cin.ignore();

        cout << "Please enter special type : ";
        string specialType;
        cin >> specialType;
        cin.ignore();

        bool isWarpSpace = (specialType == "WS");

        if (shapeName == "Circle") {
            cout << "Please enter x-ordinate of center : ";
            int centerX;
            cin >> centerX;
            cin.ignore();

            cout << "Please enter y-ordinate of center : ";
            int centerY;
            cin >> centerY;
            cin.ignore();

            cout << "Please enter radius (units) : ";
            int radius;
            cin >> radius;
            cin.ignore();

            // Create new circle and add to shapes vector
            Circle* newCircle = new Circle(shapeName, isWarpSpace);
            newCircle->setCenter(centerX, centerY);
            newCircle->setRadius(radius);

            shapes.push_back(newCircle);

            cout << "Record successfully stored. Going back to main menu ..." << endl;
        } 
        else if (shapeName == "Square") {
            vector<pair<int, int>> vertices;
            for (int i = 0; i < 4; i++) {
                cout << "Please enter x-ordinate of pt." << (i + 1) << " : ";
                int x;
                cin >> x;
                cin.ignore();

                cout << "Please enter y-ordinate of pt." << (i + 1) << " : ";
                int y;
                cin >> y;
                cin.ignore();

                vertices.push_back({x, y});
            }

            Square* newSquare = new Square(shapeName, isWarpSpace);
            newSquare->setVertices(vertices);
            shapes.push_back(newSquare);

            cout << "Record successfully stored. Going back to main menu ..." << endl;
        }
        else if (shapeName == "Rectangle") {
            vector<pair<int, int>> vertices;
            for (int i = 0; i < 4; i++) {
                cout << "Please enter x-ordinate of pt." << (i + 1) << " : ";
                int x;
                cin >> x;
                cin.ignore();

                cout << "Please enter y-ordinate of pt." << (i + 1) << " : ";
                int y;
                cin >> y;
                cin.ignore();

                vertices.push_back({x, y});
            }

            Rectangle* newRectangle = new Rectangle(shapeName, isWarpSpace);
            newRectangle->setVertices(vertices);
            shapes.push_back(newRectangle);

            cout << "Record successfully stored. Going back to main menu ..." << endl;
        }
        else if (shapeName == "Cross") {
            vector<pair<int, int>> vertices;
            for (int i = 0; i < 12; i++) {
                cout << "Please enter x-ordinate of pt." << (i + 1) << " : ";
                int x;
                cin >> x;
                cin.ignore();

                cout << "Please enter y-ordinate of pt." << (i + 1) << " : ";
                int y;
                cin >> y;
                cin.ignore();

                vertices.push_back({x, y});
            }

            Cross* newCross = new Cross(shapeName, isWarpSpace);
            newCross->setVertices(vertices);
            shapes.push_back(newCross);

            cout << "Record successfully stored. Going back to main menu ..." << endl;
        }
        else {
            cout << "Shape type '" << shapeName << "' is not supported yet." << endl;
        }
        cout << endl;
    }

    void computeArea() {
        cout << "[ Compute area (for all records) ]" << endl;
        
        if (shapes.empty()) {
            cout << "No records available!" << endl;
        } else {
            // Use polymorphism to compute area for each shape
            for (auto shape : shapes) {
                shape->computeArea(); // This will call the appropriate derived class method
            }
            cout << "Computation completed! (" << shapes.size() << " records were updated )" << endl;
        }
        cout << endl;
    }

    void printShapesReport() {
        cout << "[ Print shapes report ]" << endl;
        cout << "Total no. of records available = " << shapes.size() << endl;
        cout << endl;

        if (shapes.empty()) {
            cout << "No records available!" << endl;
        } else {
            for (size_t i = 0; i < shapes.size(); i++) {
                cout << "Shape [" << i << "]" << endl;
                cout << shapes[i]->toString() << endl;
            }
        }
        cout << endl;
    }

    void sortShapeData() {
        cout << "[ Sort shape data ]" << endl;
        
        if (shapes.empty()) {
            cout << "No records available for sorting!" << endl;
            cout << endl;
            return;
        }

        cout << "a)\tSort by area (ascending)" << endl;
        cout << "b)\tSort by area (descending)" << endl;
        cout << "c)\tSort by special type and area" << endl;
        cout << endl;
        cout << "Please select sort option ('q' to go main menu) : ";
        
        char sortOption;
        cin >> sortOption;
        cin.ignore();

        if (sortOption == 'q' || sortOption == 'Q') {
            cout << endl;
            return;
        }

        switch (sortOption) {
            case 'a':
            case 'A':
                // Sort by area ascending
                sort(shapes.begin(), shapes.end(), [](ShapeTwoD* a, ShapeTwoD* b) {
                    return a->computeArea() < b->computeArea();
                });
                cout << "Sort by area (ascending) ..." << endl;
                break;
            
            case 'b':
            case 'B':
                // Sort by area descending
                sort(shapes.begin(), shapes.end(), [](ShapeTwoD* a, ShapeTwoD* b) {
                    return a->computeArea() > b->computeArea();
                });
                cout << "Sort by area (descending) ..." << endl;
                break;
            
            case 'c':
            case 'C':
                // Sort by special type first (WS before NS), then by area descending within each group
                sort(shapes.begin(), shapes.end(), [](ShapeTwoD* a, ShapeTwoD* b) {
                    if (a->getContainsWarpSpace() != b->getContainsWarpSpace()) {
                        return a->getContainsWarpSpace() > b->getContainsWarpSpace(); // WS before NS
                    }
                    return a->computeArea() > b->computeArea(); // Within same type, area descending
                });
                cout << "Sort by special type and area ..." << endl;
                break;
            
            default:
                cout << "Invalid sort option!" << endl;
                cout << endl;
                return;
        }

        // Display sorted results
        cout << endl;
        for (size_t i = 0; i < shapes.size(); i++) {
            cout << "Shape [" << i << "]" << endl;
            cout << "Name : " << shapes[i]->getName() << endl;
            cout << "Special Type : " << (shapes[i]->getContainsWarpSpace() ? "WS" : "NS") << endl;
            cout << "Area : " << fixed << setprecision(2) << shapes[i]->computeArea() << " units square" << endl;
            cout << endl;
        }
        cout << endl;
    }

    bool processMenuChoice(int choice) {
        switch (choice) {
            case 1:
                inputSensorData();
                break;
            case 2:
                computeArea();
                break;
            case 3:
                printShapesReport();
                break;
            case 4:
                sortShapeData();
                break;
            default:
                cout << "Invalid choice! Please enter a number between 1 and 4." << endl;
                cout << endl;
                break;
        }
        return true;
    }

    void runMenu() {
        bool keepRunning = true;
        while (keepRunning) {
            displayMenu();
            int choice = getUserChoice();
            cout << endl;
            keepRunning = processMenuChoice(choice);
        }
    }
};

int main() {
    MenuSystem menu;
    menu.runMenu();
    return 0;
}
