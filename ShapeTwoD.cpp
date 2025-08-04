#include "ShapeTwoD.h"
#include <sstream>
#include <iostream>
#include <limits>

using namespace std;

ShapeTwoD::ShapeTwoD(){
  this->name = "Square";
  this->containsWarpSpace = false;
}

ShapeTwoD::ShapeTwoD(string name, bool containsWarpSpace)
  : name(name), containsWarpSpace(containsWarpSpace) {}
  
string ShapeTwoD::getName(){
  return name;
}

bool ShapeTwoD::getContainsWarpSpace(){
  return containsWarpSpace;
}

double ShapeTwoD::getArea(){
  return area;
}

string ShapeTwoD::toString(){
  stringstream ss;
  ss << "Name : " << name << endl;
  ss << "Special Type : " << (containsWarpSpace ? "WS" : "NS") << endl;
  ss << "Area : " << computeArea() << " units square" << endl;
  return ss.str();
}

void ShapeTwoD::setName(string name){
  this->name = name;
}

void ShapeTwoD::setContainsWarpSpace(bool ContainsWarpSpace){
  this->ContainsWarpSpace = ContainsWarpSpace;
}

