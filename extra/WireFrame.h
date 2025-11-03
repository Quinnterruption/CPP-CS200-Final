//
// Created by Quinn on 10/28/2025.
//

#ifndef FINALPROJECT_WIREFRAME_H
#define FINALPROJECT_WIREFRAME_H

#include <iostream>
#include <array>

using std::array;

struct coord {
    array<double, 3> coordinates{};

    coord(std::initializer_list<double> init) {
        if (init.size() != 3) {
            throw std::invalid_argument("Coord must have exactly 3 elements");
        }
        std::copy(init.begin(), init.end(), coordinates.begin());
    }

    friend std::ostream& operator<<(std::ostream& os, const coord& obj) {
        std::cout << "{" << obj[0] << ", " << obj[1] << ", " << obj[2] << "}";
        return os;
    }

    coord& operator-=(const coord& obj) {
        for (int i = 0; i < 3; i++) {
            coordinates[i] -= obj[i];
        }
        return *this;
    }

    coord& operator+=(const coord& obj) {
        for (int i = 0; i < 3; i++) {
            coordinates[i] += obj[i];
        }
        return *this;
    }

    double& operator[](std::size_t idx) {
        return coordinates[idx];
    }

    const double& operator[](std::size_t idx) const {
        return coordinates[idx];
    }
};

enum rotationFlags {
    rotateX = 1,
    rotateY = 2,
    rotateZ = 4
};

class WireFrame {
    coord getOrigin();
    array<array<double, 3>, 3> matrixMult(const array<array<double, 3>, 3>& first, const array<array<double, 3>, 3>& second);
public:
    coord topLeft;
    coord topRight;
    coord botLeft;
    coord botRight;

    WireFrame(coord topLeft, coord botRight) : topLeft(topLeft), botRight(botRight), topRight({0, 0, 0}), botLeft({0, 0, 0}) {
        topRight = {botRight[0], topLeft[1], 0};
        botLeft = {topLeft[0], botRight[1], 0};
    }

    friend std::ostream& operator << (std::ostream& os, const WireFrame& obj) {
        std::cout << obj.topLeft << "\n" << obj.botRight << "\n";
        return os;
    }

    void rotate(int axis);
    void updateLocation(coord amount);
};


#endif //FINALPROJECT_WIREFRAME_H