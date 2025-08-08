#ifndef SQUARE_H
#define SQUARE_H

#include "ShapeTwoD.h"
#include <vector>

using namespace std;

class Square : public ShapeTwoD {
private:
    vector<pair<int, int>> vertices;  // 4 vertices of the square
    vector<pair<int, int>> pointsOnPerimeter;  // Points on perimeter
    vector<pair<int, int>> pointsWithinShape;  // Points within shape

public:
    // Constructor
    Square(const string& name, bool containsWarpSpace);
    
    // Virtual destructor
    ~Square() override = default;

    // Setter for vertices
    void setVertices(const vector<pair<int, int>>& vertices);

    // Getter for vertices
    const vector<pair<int, int>>& getVertices() const { return vertices; }

    // Override virtual methods from base class
    virtual string toString() const override;
    virtual double computeArea() const override;
    virtual bool isPointInShape(int x, int y) const override;
    virtual bool isPointOnShape(int x, int y) const override;

    // Additional methods for calculating perimeter and interior points
    void calculatePerimeterPoints();
    void calculatePointsWithin();

    // Getters for calculated points
    const vector<pair<int, int>>& getPointsOnPerimeter() const { return pointsOnPerimeter; }
    const vector<pair<int, int>>& getPointsWithinShape() const { return pointsWithinShape; }

private:
    // Helper methods
    bool isPointOnLineSegment(int px, int py, int x1, int y1, int x2, int y2) const;
    int getBoundingBoxMinX() const;
    int getBoundingBoxMaxX() const;
    int getBoundingBoxMinY() const;
    int getBoundingBoxMaxY() const;
};

#endif
