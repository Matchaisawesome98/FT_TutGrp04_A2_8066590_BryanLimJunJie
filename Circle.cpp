#define _USE_MATH_DEFINES

#include "Circle.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <utility>

using namespace std;

// Constructor
Circle::Circle(const string &name, bool containsWarpSpace)
    : ShapeTwoD(name, containsWarpSpace), centerX(0), centerY(0), radius(0) {
}

// Setter methods
void Circle::setCenter(int x, int y) {
    centerX = x;
    centerY = y;
    // Recalculate points when center changes
    calculatePerimeterPoints();
    calculatePointsWithin();
}

void Circle::setRadius(int r) {
    radius = r;
    // Recalculate points when radius changes
    calculatePerimeterPoints();
    calculatePointsWithin();
}

// Override toString method to include circle-specific information
string Circle::toString() const {
    stringstream ss;
    ss << "Name : " << getName() << endl;
    ss << "Special Type : " << (getContainsWarpSpace() ? "WS" : "NS") << endl;
    ss << "Area : " << fixed << setprecision(2) << computeArea() << " units square" << endl;

    // For circles, we show vertices count and center/radius info
    ss << "Vertices : 1" << endl;
    ss << "Center Point : (" << centerX << ", " << centerY << ")" << endl;
    ss << "Radius : " << radius << endl;

    // Show perimeter points (only 4 cardinal points as per assignment requirement)
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

// Compute area of circle: π * r²
double Circle::computeArea() const {
    return M_PI * radius * radius;
}

// Check if a point is inside the circle (distance from center < radius)
bool Circle::isPointInShape(int x, int y) const {
    double distance = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));
    return distance < radius;
}

// Check if a point is on the circle's circumference (distance from center = radius)
bool Circle::isPointOnShape(int x, int y) const {
    double distance = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));
    // Use a small tolerance for floating point comparison
    return abs(distance - radius) < 0.5; // Within 0.5 units of the radius
}

// Calculate points on the perimeter (circumference) of the circle
void Circle::calculatePerimeterPoints() {
    pointsOnPerimeter.clear();

    // Test case shows: (13,14), (16,11), (19,14), (16,17) for center(16,14) radius=3
    pointsOnPerimeter.push_back({centerX, centerY + radius});      // North
    pointsOnPerimeter.push_back({centerX, centerY - radius});      // South  
    pointsOnPerimeter.push_back({centerX + radius, centerY});      // East
    pointsOnPerimeter.push_back({centerX - radius, centerY});      // West

    // Sort points for consistent output
    sort(pointsOnPerimeter.begin(), pointsOnPerimeter.end());
}

// Calculate all integer coordinate points that are completely within the circle
void Circle::calculatePointsWithin() {
    pointsWithinShape.clear();

    // Check all integer points in a bounding box around the circle
    for (int x = centerX - radius; x <= centerX + radius; x++) {
        for (int y = centerY - radius; y <= centerY + radius; y++) {
            if (isPointInShape(x, y)) {
                pointsWithinShape.push_back({x, y});
            }
        }
    }

    // Sort points for consistent output
    sort(pointsWithinShape.begin(), pointsWithinShape.end());
}
