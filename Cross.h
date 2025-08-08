#ifndef CROSS_H
#define CROSS_H

#include "ShapeTwoD.h"
#include <vector>

using namespace std;

class Cross : public ShapeTwoD {
private:
    vector<pair<int, int>> vertices;  // 12 vertices of the cross
    vector<pair<int, int>> pointsOnPerimeter;  // Points on perimeter
    vector<pair<int, int>> pointsWithinShape;  // Points within shape

public:
    // Constructor
    Cross(const string& name, bool containsWarpSpace);
    
    // Virtual destructor
    ~Cross() override = default;

    // Setter for vertices
    void setVertices(const vector<pair<int, int>>& vertices);

    // Getter for vertices
    const vector<pair<int, int>>& getVertices() const { return vertices; }

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

private:
    // Helper methods
    bool isPointOnLineSegment(int px, int py, int x1, int y1, int x2, int y2) const;
    double calculatePolygonArea() const;
    int getBoundingBoxMinX() const;
    int getBoundingBoxMaxX() const;
    int getBoundingBoxMinY() const;
    int getBoundingBoxMaxY() const;
};

#endif
