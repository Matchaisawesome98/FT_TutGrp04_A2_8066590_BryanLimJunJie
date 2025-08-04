#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>
#include <iomanip>

#include "ShapeTwoD.h"
//#include "Square.h"
#include "Circle.h"
//#include "Rectangle.h"
//#include "Cross.h"

using namespace std;

void displayMenu(){
    int choice;
    
    cout << left << setw(15) << "Student ID" << ": 8066590" << endl;
    cout << left << setw(15) << "Student Name" << ": Bryan Lim Jun Jie" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Welcome to Assn2 program!\n" << endl;
    cout << left << setw(5) << "1)" << "Input Sensor Data"<< endl;
    cout << left << setw(5) << "2)" << "Compute area(for all records)"<< endl;
    cout << left << setw(5) << "3)" << "Print shapes report"<< endl;
    cout << left << setw(5) << "4)" << "Sort shapes data"<< endl;
    cout << "\nPlease enter your choice : ";
    cin >> choice;
    
    switch(choice){
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      default:
        cout << "Invalid! please choose 1-4"<< endl;
        break;
    }
}

int main() {
    displayMenu();
    return 0;
}
