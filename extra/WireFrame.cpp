//
// Created by Quinn on 10/28/2025.
//

#include "WireFrame.h"
#include <cmath>

#define matrix3 std::array<std::array<double, 3>, 3>

const matrix3 xRotate = {{{1, 0, 0},
                    {0, cos(M_PI / 180), -sin(M_PI / 180)},
                    {0, sin(M_PI / 180), cos(M_PI / 180)}}};
const matrix3 yRotate = {{{cos(M_PI / 180), 0, sin(M_PI / 180)},
                    {0, 1, 0},
                    {-sin(M_PI / 180), 0, cos(M_PI / 180)}}};
const matrix3 zRotate = {{{cos(M_PI / 180), -sin(M_PI / 180), 0},
                    {sin(M_PI / 180), cos(M_PI / 180), 0},
                    {0, 0, 1}}};


void WireFrame::rotate(int axis) {
    matrix3 rotateMatrix = {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
    if ((axis & rotateX) == rotateX) {
        rotateMatrix = matrixMult(rotateMatrix, xRotate);
    }
    if ((axis & rotateY) == rotateY) {
        rotateMatrix = matrixMult(rotateMatrix, yRotate);
    }
    if ((axis & rotateZ) == rotateZ) {
        rotateMatrix = matrixMult(rotateMatrix, zRotate);
    }
    coord midpoint = getOrigin();
    topLeft -= midpoint;
    topRight -= midpoint;
    botLeft -= midpoint;
    botRight -= midpoint;
    for (int i = 0; i < 3; i++) {
        topLeft[i] = topLeft[0] * rotateMatrix[i][0] + topLeft[1] * rotateMatrix[i][1] + topLeft[2] * rotateMatrix[i][2];
        topRight[i] = topRight[0] * rotateMatrix[i][0] + topRight[1] * rotateMatrix[i][1] + topRight[2] * rotateMatrix[i][2];
        botLeft[i] = botLeft[0] * rotateMatrix[i][0] + botLeft[1] * rotateMatrix[i][1] + botLeft[2] * rotateMatrix[i][2];
        botRight[i] = botRight[0] * rotateMatrix[i][0] + botRight[1] * rotateMatrix[i][1] + botRight[2] * rotateMatrix[i][2];
    }
    topLeft += midpoint;
    topRight += midpoint;
    botLeft += midpoint;
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

matrix3 WireFrame::matrixMult(const matrix3& first, const matrix3& second) {
    matrix3 result{};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = first[i][0] * second[0][j] + first[i][1] * second[1][j] + first[i][2] * second[2][j];
        }
    }
    return result;
}

void WireFrame::updateLocation(coord amount) {
    topLeft += amount;
    topRight += amount;
    botLeft += amount;
    botRight += amount;
}