#include "ShapeTwoD.h"
#include <sstream>
#include <iostream>
#include <limits>

using namespace std;

// Constructor
ShapeTwoD::ShapeTwoD(const string& name, bool containsWarpSpace)
    : name(name), containsWarpSpace(containsWarpSpace) {}

// Getter methods
string ShapeTwoD::getName() const {
    return name;
}

bool ShapeTwoD::getContainsWarpSpace() const {
    return containsWarpSpace;
}

string ShapeTwoD::toString() const {
    stringstream ss;
    ss << "Name : " << name << endl;
    ss << "Special Type : " << (containsWarpSpace ? "WS" : "NS") << endl;
    ss << "Area : " << computeArea() << " units square" << endl;
    return ss.str();
}

// Setter methods
void ShapeTwoD::setName(const string& name) {
    this->name = name;
}

void ShapeTwoD::setContainsWarpSpace(bool containsWarpSpace) {
    this->containsWarpSpace = containsWarpSpace;
}