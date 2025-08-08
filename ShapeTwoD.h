#ifndef SHAPE2D_H
#define SHAPE2D_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Base class ShapeTwoD
class ShapeTwoD {
private:
    string name;
    bool containsWarpSpace;

public:
    // Constructor
    ShapeTwoD(const string& name, bool containsWarpSpace);

    // Virtual destructor
    virtual ~ShapeTwoD() = default;

    // Getter methods
    string getName() const;
    bool getContainsWarpSpace() const;
    virtual string toString() const;

    // Pure virtual methods that must be implemented by derived classes
    virtual double computeArea() const = 0;
    virtual bool isPointInShape(int x, int y) const = 0;
    virtual bool isPointOnShape(int x, int y) const = 0;

    // Setter methods
    void setName(const string& name);
    void setContainsWarpSpace(bool containsWarpSpace);
};

#endif // SHAPE2D_H