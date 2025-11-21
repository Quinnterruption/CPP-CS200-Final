//
// Created by Quinn on 10/28/2025.
//

#ifndef FINALPROJECT_WIREFRAME_H
#define FINALPROJECT_WIREFRAME_H
#include <iostream>
#include <array>

#define matrix3 std::array<std::array<double, 3>, 3>

using std::array;

struct coord {
    array<double, 3> coordinates{};

    coord() = default;

    coord(const std::initializer_list<double> init) {
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

    double& operator[](const std::size_t idx) {
        return coordinates[idx];
    }

    const double& operator[](const std::size_t idx) const {
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
    static matrix3 matrixMult(const matrix3& first, const matrix3& second);

    coord midPoint;
    int rotateFlags = 0;
public:
    array<coord, 8> coordinates;

    WireFrame(std::initializer_list<coord> init);
    WireFrame(const coord &topLeft, double height, double length, double depth);

    /* DEPRECATED
    friend std::ostream& operator << (std::ostream& os, const WireFrame& obj) {
        std::cout << obj.topLeft << "\n" << obj.botRight << "\n";
        return os;
    }*/

    void setRotation(int axis);
    void toggleRotation(int axis);
    void rotate();
    void updateLocation(const coord &amount);
};


#endif //FINALPROJECT_WIREFRAME_H