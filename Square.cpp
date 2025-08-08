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
    ss << "Area : " << fixed << setprecision(0) << computeArea() << " units square" << endl;

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

// Compute area using the shoelace formula
double Square::computeArea() const {
    if (vertices.size() != 4) return 0.0;
    
    // For a square, we can calculate area using the distance between adjacent vertices
    // Area = side_length^2
    int dx = vertices[1].first - vertices[0].first;
    int dy = vertices[1].second - vertices[0].second;
    double sideLength = sqrt(dx * dx + dy * dy);
    
    // For axis-aligned squares, use simpler calculation
    if (dy == 0) { // horizontal side
        sideLength = abs(dx);
    } else if (dx == 0) { // vertical side
        sideLength = abs(dy);
    }
    
    return sideLength * sideLength;
}

// Check if point is inside the square using ray casting algorithm
bool Square::isPointInShape(int x, int y) const {
    if (vertices.size() != 4) return false;
    
    int intersections = 0;
    
    // Ray casting: cast a ray from point to the right and count intersections
    for (size_t i = 0; i < 4; i++) {
        int x1 = vertices[i].first;
        int y1 = vertices[i].second;
        int x2 = vertices[(i + 1) % 4].first;
        int y2 = vertices[(i + 1) % 4].second;
        
        // Check if ray intersects this edge
        if (((y1 > y) != (y2 > y)) && 
            (x < (x2 - x1) * (y - y1) / (y2 - y1) + x1)) {
            intersections++;
        }
    }
    
    return (intersections % 2 == 1);
}

// Check if point is on the perimeter of the square
bool Square::isPointOnShape(int x, int y) const {
    if (vertices.size() != 4) return false;
    
    // Check if point lies on any of the four edges
    for (size_t i = 0; i < 4; i++) {
        int x1 = vertices[i].first;
        int y1 = vertices[i].second;
        int x2 = vertices[(i + 1) % 4].first;
        int y2 = vertices[(i + 1) % 4].second;
        
        if (isPointOnLineSegment(x, y, x1, y1, x2, y2)) {
            return true;
        }
    }
    
    return false;
}

// Helper method to check if point is on line segment
bool Square::isPointOnLineSegment(int px, int py, int x1, int y1, int x2, int y2) const {
    // Check if point is collinear with line segment
    int crossProduct = (py - y1) * (x2 - x1) - (px - x1) * (y2 - y1);
    if (crossProduct != 0) return false;
    
    // Check if point is within the bounds of the line segment
    int minX = min(x1, x2);
    int maxX = max(x1, x2);
    int minY = min(y1, y2);
    int maxY = max(y1, y2);
    
    return (px >= minX && px <= maxX && py >= minY && py <= maxY);
}

// Calculate points on perimeter
void Square::calculatePerimeterPoints() {
    pointsOnPerimeter.clear();
    
    if (vertices.size() != 4) return;
    
    // Find all integer points on each edge of the square
    for (size_t i = 0; i < 4; i++) {
        int x1 = vertices[i].first;
        int y1 = vertices[i].second;
        int x2 = vertices[(i + 1) % 4].first;
        int y2 = vertices[(i + 1) % 4].second;
        
        // Generate points along this edge
        if (x1 == x2) { // vertical line
            int minY = min(y1, y2);
            int maxY = max(y1, y2);
            for (int y = minY; y <= maxY; y++) {
                pointsOnPerimeter.push_back({x1, y});
            }
        } else if (y1 == y2) { // horizontal line
            int minX = min(x1, x2);
            int maxX = max(x1, x2);
            for (int x = minX; x <= maxX; x++) {
                pointsOnPerimeter.push_back({x, y1});
            }
        } else {
            // Diagonal line - use Bresenham's line algorithm or simple interpolation
            int dx = abs(x2 - x1);
            int dy = abs(y2 - y1);
            int sx = (x1 < x2) ? 1 : -1;
            int sy = (y1 < y2) ? 1 : -1;
            int err = dx - dy;
            
            int x = x1, y = y1;
            while (true) {
                pointsOnPerimeter.push_back({x, y});
                if (x == x2 && y == y2) break;
                
                int e2 = 2 * err;
                if (e2 > -dy) {
                    err -= dy;
                    x += sx;
                }
                if (e2 < dx) {
                    err += dx;
                    y += sy;
                }
            }
        }
    }
    
    // Remove duplicates and sort
    sort(pointsOnPerimeter.begin(), pointsOnPerimeter.end());
    pointsOnPerimeter.erase(unique(pointsOnPerimeter.begin(), pointsOnPerimeter.end()), 
                           pointsOnPerimeter.end());
}

// Calculate points within the shape
void Square::calculatePointsWithin() {
    pointsWithinShape.clear();
    
    if (vertices.size() != 4) return;
    
    // Check all points in bounding box
    int minX = getBoundingBoxMinX();
    int maxX = getBoundingBoxMaxX();
    int minY = getBoundingBoxMinY();
    int maxY = getBoundingBoxMaxY();
    
    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            if (isPointInShape(x, y)) {
                pointsWithinShape.push_back({x, y});
            }
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
