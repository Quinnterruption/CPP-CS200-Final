//
// Created by Quinn on 10/28/2025.
//

#include "WireFrame.h"
#include <cmath>
#include <array>
#include <iostream>

#define matrix3 std::array<std::array<double, 3>, 3>

matrix3 xRotate = {{{1, 0, 0},
                    {0, cos(M_PI / 180), -sin(M_PI / 180)},
                    {0, sin(M_PI / 180), cos(M_PI / 180)}}};
matrix3 yRotate = {{{cos(M_PI / 180), 0, sin(M_PI / 180)},
                    {0, 1, 0},
                    {-sin(M_PI / 180), 0, cos(M_PI / 180)}}};
matrix3 zRotate = {{{cos(M_PI / 180), -sin(M_PI / 180), 0},
                    {sin(M_PI / 180), cos(M_PI / 180), 0},
                    {0, 0, 1}}};

// topLeft.x * [0][0] + topLeft.x * [0][1] + topLeft.x * [0][2] +
// topLeft.x * [0][0] + topLeft.x * [0][1] + topLeft.x * [0][2] +
// topLeft.x * [0][0] + topLeft.x * [0][1] + topLeft.x * [0][2]

// topLeft.x * cos(1) + topLeft.z * sin(1) +
// topLeft.x * cos(1) + topLeft.y * -sin(1)

// topLeft.x * cos(1)cos(1) + topLeft.y * (sin(1)sin(1)cos(1)-cos(1)sin(1)) + topLeft.z * (cos(1)sin(1)cos(1)+sin(1)sin(1))

void WireFrame::rotate(int axis) {
    matrix3 rotateMatrix = {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
    if ((axis & 1) == 1) {
        rotateMatrix = matrixMult(rotateMatrix, xRotate);
    }
    if ((axis & 2) == 2) {
        rotateMatrix = matrixMult(rotateMatrix, yRotate);
    }
    if ((axis & 4) == 4) {
        rotateMatrix = matrixMult(rotateMatrix, zRotate);
    }
    coord midpoint = getOrigin();
    topLeft -= midpoint;
    botRight -= midpoint;
    for (int i = 0; i < 3; i++) {
        topLeft[i] = topLeft[0] * rotateMatrix[i][0] + topLeft[1] * rotateMatrix[i][1] + topLeft[2] * rotateMatrix[i][2];
        botRight[i] = botRight[0] * rotateMatrix[i][0] + botRight[1] * rotateMatrix[i][1] + botRight[2] * rotateMatrix[i][2];
    }
//    topLeft.x = topLeft.x * rotateMatrix[0][0] + topLeft.y * rotateMatrix[0][1] + topLeft.z * rotateMatrix[0][2];
//    topLeft.y = topLeft.x * rotateMatrix[1][0] + topLeft.y * rotateMatrix[1][1] + topLeft.z * rotateMatrix[1][2];
//    topLeft.z = topLeft.x * rotateMatrix[2][0] + topLeft.y * rotateMatrix[2][1] + topLeft.z * rotateMatrix[2][2];
//
//    botRight.x = botRight.x * rotateMatrix[0][0] + botRight.y * rotateMatrix[0][1] + botRight.z * rotateMatrix[0][2];
//    botRight.y = botRight.x * rotateMatrix[1][0] + botRight.y * rotateMatrix[1][1] + botRight.z * rotateMatrix[1][2];
//    botRight.z = botRight.x * rotateMatrix[2][0] + botRight.y * rotateMatrix[2][1] + botRight.z * rotateMatrix[2][2];
//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < 3; j++) {
//            std::cout << rotateMatrix[i][j] << ' ';
//        }
//        std::cout << '\n';
//    }
    topLeft += midpoint;
    botRight += midpoint;
}

coord WireFrame::getOrigin() {
    // Midpoint Formula: ((x1+x2)/2, (y1+y2)/2)
    // 3d Midpoint Formula ((x1+x2)/2, (y1+y2)/2, (z1+z2)/2)
    double x = (topLeft[0] + botRight[0])/2;
    double y = (topLeft[1] + botRight[1])/2;
    double z = (topLeft[2] + botRight[2])/2;

    return {x, y, z};
}

matrix3 WireFrame::matrixMult(matrix3 first, matrix3 second) {
    matrix3 result{};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = first[i][0] * second[0][j] + first[i][1] * second[1][j] + first[i][2] * second[2][j];
        }
    }
//    result[0][0] = first[0][0] * second[0][0] + first[0][1] * second[1][0] + first[0][2] * second[2][0];
//    result[0][1] = first[0][0] * second[0][1] + first[0][1] * second[1][1] + first[0][2] * second[2][1];
//    result[0][2] = first[0][0] * second[0][2] + first[0][1] * second[1][2] + first[0][2] * second[2][2];
//    result[1][0] = first[1][0] * second[0][0] + first[1][1] * second[1][0] + first[1][2] * second[2][0];
//    result[1][1] = first[1][0] * second[0][1] + first[1][1] * second[1][1] + first[1][2] * second[2][1];
//    result[1][2] = first[1][0] * second[0][2] + first[1][1] * second[1][2] + first[1][2] * second[2][2];
//    result[2][0] = first[2][0] * second[0][0] + first[2][1] * second[1][0] + first[2][2] * second[2][0];
//    result[2][1] = first[2][0] * second[0][1] + first[2][1] * second[1][1] + first[2][2] * second[2][1];
//    result[2][2] = first[2][0] * second[0][2] + first[2][1] * second[1][2] + first[2][2] * second[2][2];
    return result;
}

// x' = x * [0][0] + y * [0][1] + z * [0][2]
// y' = x * [1][0] + y * [1][1] + z * [1][2]
// z' = x * [2][0] + y * [2][1] + z * [2][2]