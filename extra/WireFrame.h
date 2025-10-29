//
// Created by Quinn on 10/28/2025.
//

#ifndef FINALPROJECT_WIREFRAME_H
#define FINALPROJECT_WIREFRAME_H

#include <iostream>
#include <array>

using std::array;

struct coord {
    double x;
    double y;
    double z;

    coord(double x, double y, double z) : x(x), y(y), z(z) {}
    coord() : x(0), y(0), z(0) {}
    void update(double _x, double _y, double _z) {
        x = _x;
        y = _y;
        z = _z;
    }
    friend std::ostream& operator << (std::ostream& os, coord obj) {
        std::cout << "{" << obj.x << ", " << obj.y << ", " << obj.z << "}";
        return os;
    }
    coord& operator-=(coord obj) {
        x -= obj.x;
        y -= obj.y;
        z -= obj.z;
        return *this;
    }
    coord& operator+=(coord obj) {
        x += obj.x;
        y += obj.y;
        z += obj.z;
        return *this;
    }
};

enum rotationFlags {
    rotateX = 1,
    rotateY = 2,
    rotateZ = 4
};

class WireFrame {
    coord topLeft;
    coord botRight;
    coord getOrigin();
    array<array<double, 3>, 3> matrixMult(array<array<double, 3>, 3> first, array<array<double, 3>, 3> second);
public:
    WireFrame(coord topLeft, coord botRight) : topLeft(topLeft), botRight(botRight) {}
    friend std::ostream& operator << (std::ostream& os, WireFrame obj) {
        std::cout << obj.topLeft << "\n" << obj.botRight << "\n";
        return os;
    }
    void rotate(int axis);
};


#endif //FINALPROJECT_WIREFRAME_H
