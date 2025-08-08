#include "Square.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

// Constructor
Square::Square(const string& name, bool containsWarpSpace)
    : ShapeTwoD(name, containsWarpSpace) {}

// Setter for vertices
void Square::setVertices(const vector<pair<int, int>>& vertices) {
    if (vertices.size() == 4) {
        this->vertices = vertices;
        // Sort vertices for consistent ordering
        sort(this->vertices.begin(), this->vertices.end());
        calculatePerimeterPoints();
        calculatePointsWithin();
    }
}

// Override toString method
string Square::toString() const {
    stringstream ss;
    ss << "Name : " << getName() << endl;
    ss << "Special Type : " << (getContainsWarpSpace() ? "WS" : "NS") << endl;
    ss << "Area : " << fixed << setprecision(2) << computeArea() << " units square" << endl;

    // Show vertices
    ss << "Vertices :" << endl;
    for (size_t i = 0; i < vertices.size(); i++) {
        ss << "Point [" << i << "] : (" << vertices[i].first << ", " << vertices[i].second << ")" << endl;
    }

    // Show perimeter points
    ss << "Points on perimeter : ";
    if (pointsOnPerimeter.empty()) {
        ss << "none!";
    } else {
        for (size_t i = 0; i < pointsOnPerimeter.size(); i++) {
            if (i > 0) ss << ", ";
            ss << "(" << pointsOnPerimeter[i].first << ", " << pointsOnPerimeter[i].second << ")";
        }
    }
    ss << endl;

    // Show points within shape
    ss << "Points within shape : ";
    if (pointsWithinShape.empty()) {
        ss << "none!";
    } else {
        for (size_t i = 0; i < pointsWithinShape.size(); i++) {
            if (i > 0) ss << ", ";
            ss << "(" << pointsWithinShape[i].first << ", " << pointsWithinShape[i].second << ")";
        }
    }
    ss << endl;

    return ss.str();
}

// Compute area - for axis-aligned squares/rectangles
double Square::computeArea() const {
    if (vertices.size() != 4) return 0.0;
    
    // Find bounding box to calculate area
    int minX = getBoundingBoxMinX();
    int maxX = getBoundingBoxMaxX();
    int minY = getBoundingBoxMinY();
    int maxY = getBoundingBoxMaxY();
    
    double width = maxX - minX;
    double height = maxY - minY;
    
    return width * height;
}

// Check if point is inside the square (strictly inside, not on boundary)
bool Square::isPointInShape(int x, int y) const {
    if (vertices.size() != 4) return false;
    
    int minX = getBoundingBoxMinX();
    int maxX = getBoundingBoxMaxX();
    int minY = getBoundingBoxMinY();
    int maxY = getBoundingBoxMaxY();
    
    // Point must be strictly inside (not on the boundary)
    return (x > minX && x < maxX && y > minY && y < maxY);
}

// Check if point is on the perimeter of the square
bool Square::isPointOnShape(int x, int y) const {
    if (vertices.size() != 4) return false;
    
    int minX = getBoundingBoxMinX();
    int maxX = getBoundingBoxMaxX();
    int minY = getBoundingBoxMinY();
    int maxY = getBoundingBoxMaxY();
    
    // Point is on perimeter if it's on any edge
    bool onVerticalEdge = (x == minX || x == maxX) && (y >= minY && y <= maxY);
    bool onHorizontalEdge = (y == minY || y == maxY) && (x >= minX && x <= maxX);
    
    return onVerticalEdge || onHorizontalEdge;
}

// Calculate perimeter points - general algorithm for any square size
void Square::calculatePerimeterPoints() {
    pointsOnPerimeter.clear();
    
    if (vertices.size() != 4) return;
    
    int minX = getBoundingBoxMinX();
    int maxX = getBoundingBoxMaxX();
    int minY = getBoundingBoxMinY();
    int maxY = getBoundingBoxMaxY();
    
    // GENERAL ALGORITHM: Find all non-corner points on the square perimeter
    // This works for any square size and coordinates
    
    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            // Include point if it's on the shape boundary but not a corner vertex
            if (isPointOnShape(x, y) && !isCornerPoint(x, y, minX, maxX, minY, maxY)) {
                pointsOnPerimeter.push_back({x, y});
            }
        }
    }
    
    // Sort points for consistent output
    sort(pointsOnPerimeter.begin(), pointsOnPerimeter.end());
}

// Helper function to check if point is a corner vertex
bool Square::isCornerPoint(int x, int y, int minX, int maxX, int minY, int maxY) const {
    return (x == minX || x == maxX) && (y == minY || y == maxY);
}

// Calculate points within the shape (strictly inside) - general algorithm
void Square::calculatePointsWithin() {
    pointsWithinShape.clear();
    
    if (vertices.size() != 4) return;
    
    int minX = getBoundingBoxMinX();
    int maxX = getBoundingBoxMaxX();
    int minY = getBoundingBoxMinY();
    int maxY = getBoundingBoxMaxY();
    
    // GENERAL ALGORITHM: Check all integer points strictly inside the square
    // This works for any square size and coordinates
    
    for (int x = minX + 1; x < maxX; x++) {
        for (int y = minY + 1; y < maxY; y++) {
            pointsWithinShape.push_back({x, y});
        }
    }
    
    sort(pointsWithinShape.begin(), pointsWithinShape.end());
}

// Helper methods for bounding box
int Square::getBoundingBoxMinX() const {
    if (vertices.empty()) return 0;
    int minX = vertices[0].first;
    for (const auto& vertex : vertices) {
        minX = min(minX, vertex.first);
    }
    return minX;
}

int Square::getBoundingBoxMaxX() const {
    if (vertices.empty()) return 0;
    int maxX = vertices[0].first;
    for (const auto& vertex : vertices) {
        maxX = max(maxX, vertex.first);
    }
    return maxX;
}

int Square::getBoundingBoxMinY() const {
    if (vertices.empty()) return 0;
    int minY = vertices[0].second;
    for (const auto& vertex : vertices) {
        minY = min(minY, vertex.second);
    }
    return minY;
}

int Square::getBoundingBoxMaxY() const {
    if (vertices.empty()) return 0;
    int maxY = vertices[0].second;
    for (const auto& vertex : vertices) {
        maxY = max(maxY, vertex.second);
    }
    return maxY;
}
