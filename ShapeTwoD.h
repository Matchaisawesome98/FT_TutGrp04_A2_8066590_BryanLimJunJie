#ifndef SHAPETWOD_H
#define SHAPETWOD_H
#include <string>
#include <vector>

using namespace std;

class ShapeTwoD{
private: 
  string name;
  bool containsWarpSpace;
public:
  //default constructor
  ShapeTwoD();
  
  //constructor
  ShapeTwoD(string name, bool containsWarpSpace);
  
  //virtual destructor
  virtual ~ShapeTwoD() = default;
  
  //getters
  string getName();
  bool getContainsWarpSpace();
  virtual string toString() const;
  
  //setters
  void setName(string name);
  void setContainsWarpSpace(bool containsWarpSpace);
  
  virtual double computeArea() const = 0;
  virtual bool isPointInShape(int x, int y) const = 0;
  virtual bool isPointOnShape(int x, int y) const = 0;
};

#endif //SHAPE2D_H
