#ifndef CIRCLE_H
#define CIRCLE_H

#include "ShapeTwoD.h"
#include <vector>

using namespace std;

class Circle:public ShapeTwoD {
    // Constructor
    Circle(const string& name, bool containsWarpSpace);
    // Virtual destructor
    ~Circle() override;

    virtual string toString();
    virtual double computeArea();
    virtual bool isPointInShape(int, int);
    virtual bool isPointOnShape(int, int);
    virtual void calculatePerimeter();
    virtual void calculatePointsWithin();
};


#endif