//
// Created by Quinn on 10/28/2025.
//

#include "wireFrame.h"
#include <cmath>

const double DEGREES = 2;
const double THETA = DEGREES * M_PI / 180.0;

const matrix3 xRotate = {{{1.0, 0.0, 0.0},
                    {0.0, cos(THETA), -sin(THETA)},
                    {0.0, sin(THETA), cos(THETA)}}};
const matrix3 yRotate = {{{cos(THETA), 0.0, sin(THETA)},
                    {0.0, 1.0, 0.0},
                    {-sin(THETA), 0.0, cos(THETA)}}};
const matrix3 zRotate = {{{cos(THETA), -sin(THETA), 0.0},
                    {sin(THETA), cos(THETA), 0.0},
                    {0.0, 0.0, 1.0}}};


void wireFrame::setRotation(int axis) {
    rotateFlags = axis;
}

void wireFrame::toggleRotation(int axis) {
    rotateFlags ^= axis;
}

void wireFrame::rotate() {
    if (rotateFlags == 0 || rotateFlags > (rotateX | rotateY | rotateZ)) return;
    matrix3 rotateMatrix = {{{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}}};
    if ((rotateFlags & rotateX) == rotateX) {
        rotateMatrix = matrixMult(rotateMatrix, xRotate);
    }
    if ((rotateFlags & rotateY) == rotateY) {
        rotateMatrix = matrixMult(rotateMatrix, yRotate);
    }
    if ((rotateFlags & rotateZ) == rotateZ) {
        rotateMatrix = matrixMult(rotateMatrix, zRotate);
    }
//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < 3; j++) {
//            std::cout << rotateMatrix[i][j] << ' ';
//        }
//        std::cout << '\n';
//    }
    for (int i = 0; i < 8; i++) {
        coordinates[i] -= midPoint;
    }
    std::array<coord, 8> newCoord = coordinates;
//    for (int i = 0; i < 8; i++) {
//        std::cout << newCoord[i] << '\n';
//    }
//    topLeft -= midpoint;
//    topRight -= midpoint;
//    botLeft -= midpoint;
//    botRight -= midpoint;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            newCoord[j][i] = coordinates[j][0] * rotateMatrix[i][0] + coordinates[j][1] * rotateMatrix[i][1] + coordinates[j][2] * rotateMatrix[i][2];
//            std::cout << newCoord[j][i] << ", ";
        }
//        std::cout << '\n';
    }
//    std::cout << '\n';
//    for (int i = 0; i < 3; i++) {
//        topLeft[i] = topLeft[0] * rotateMatrix[i][0] + topLeft[1] * rotateMatrix[i][1] + topLeft[2] * rotateMatrix[i][2];
//        topRight[i] = topRight[0] * rotateMatrix[i][0] + topRight[1] * rotateMatrix[i][1] + topRight[2] * rotateMatrix[i][2];
//        botLeft[i] = botLeft[0] * rotateMatrix[i][0] + botLeft[1] * rotateMatrix[i][1] + botLeft[2] * rotateMatrix[i][2];
//        botRight[i] = botRight[0] * rotateMatrix[i][0] + botRight[1] * rotateMatrix[i][1] + botRight[2] * rotateMatrix[i][2];
//    }
//    for (int i = 0; i < 8; i++) {
//        std::cout << newCoord[i] << '\n';
//    }
    for (int i = 0; i < 8; i++) {
        newCoord[i] += midPoint;
    }
//    for (int i = 0; i < 8; i++) {
//        std::cout << newCoord[i] << '\n';
//    }
    coordinates = newCoord;
}

coord wireFrame::getOrigin() {
    double x = (coordinates[0][0] + coordinates[5][0]) / 2.0;
    double y = (coordinates[0][1] + coordinates[5][1]) / 2.0;
    double z = (coordinates[0][2] + coordinates[5][2]) / 2.0;

    return {x, y, z};
}

//coord WireFrame::getOrigin() {
//    // Midpoint Formula: ((x1+x2)/2, (y1+y2)/2)
//    // 3d Midpoint Formula ((x1+x2)/2, (y1+y2)/2, (z1+z2)/2)
//    double x = (topLeft[0] + botRight[0])/2;
//    double y = (topLeft[1] + botRight[1])/2;
//    double z = (topLeft[2] + botRight[2])/2;
//
//    return {x, y, z};
//}

matrix3 wireFrame::matrixMult(const matrix3& first, const matrix3& second) {
    matrix3 result{};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = first[i][0] * second[0][j] + first[i][1] * second[1][j] + first[i][2] * second[2][j];
        }
    }
    return result;
}

void wireFrame::updateLocation(coord amount) {
    for (int i = 0; i < 8; i++) {
        coordinates[i] += amount;
    }
    midPoint += amount;
//    topLeft += amount;
//    topRight += amount;
//    botLeft += amount;
//    botRight += amount;
}

wireFrame::wireFrame(std::initializer_list<coord> init) {
    if (init.size() != 8) {
        throw std::invalid_argument("Coordinates must have exactly 8 elements");
    }
    std::copy(init.begin(), init.end(), coordinates.begin());
}

wireFrame::wireFrame(coord topLeft, double height, double length, double depth) {
    for (coord& coordinate : coordinates) {
        coordinate = topLeft;
    }
    coordinates[1] += {length, 0, 0};
    coordinates[2] += {length, 0, depth};
    coordinates[3] += {0, 0, depth};
    coordinates[4] += {0, height, depth};
    coordinates[5] += {length, height, depth};
    coordinates[6] += {length, height, 0};
    coordinates[7] += {0, height, 0};
    midPoint = getOrigin();
}
