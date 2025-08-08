#ifndef CIRCLE_H
#define CIRCLE_H

#include "ShapeTwoD.h"
#include <vector>

using namespace std;

class Circle:public ShapeTwoD {
private:
    int centerX, centerY;  // Center coordinates
    int radius;            // Radius of the circle
    vector<pair<int, int>> pointsOnPerimeter;  // Points on perimeter
    vector<pair<int, int>> pointsWithinShape;  // Points within shape

public:
    // Constructor
    Circle(const string& name, bool containsWarpSpace);
    // Virtual destructor
    ~Circle() override = default;

    // Setters for circle-specific properties
    void setCenter(int x, int y);
    void setRadius(int r);

    // Getters for circle-specific properties
    int getCenterX() const { return centerX; }
    int getCenterY() const { return centerY; }
    int getRadius() const { return radius; }

    // Override virtual methods from base class
    string toString() const override;
    double computeArea() const override;
    bool isPointInShape(int x, int y) const override;
    bool isPointOnShape(int x, int y) const override;

    // Additional methods for calculating perimeter and interior points
    void calculatePerimeterPoints();
    void calculatePointsWithin();

    // Getters for calculated points
    const vector<pair<int, int>>& getPointsOnPerimeter() const { return pointsOnPerimeter; }
    const vector<pair<int, int>>& getPointsWithinShape() const { return pointsWithinShape; }
};


#endif