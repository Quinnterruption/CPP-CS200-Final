//
// Created by Quinn on 11/1/2025.
//

#ifndef FINALPROJECT_GAMEWINDOWBUFFER_H
#define FINALPROJECT_GAMEWINDOWBUFFER_H
#include <Windows.h>
#include "WireFrame.h"
#include <cmath>


struct GameWindowBuffer {
    unsigned char* memory = nullptr;
    int FOV = 90;
    int w = 0;
    int h = 0;

    void drawAtSafe(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
        if (x >= w || y >= h || x < 0 || y < 0) {
            return;
        }

        memory[4 * (x + y * w) + 0] = b;
        memory[4 * (x + y * w) + 1] = g;
        memory[4 * (x + y * w) + 2] = r;
        memory[4 * (x + y * w) + 3] = 0;
    }

    void clear(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0) {
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                memory[4 * (x + y * w) + 0] = b;
                memory[4 * (x + y * w) + 1] = g;
                memory[4 * (x + y * w) + 2] = r;
                memory[4 * (x + y * w) + 3] = 0;
            }
        }
    }

    void drawLine(int x1, int y1, int x2, int y2) {
        double m = static_cast<double>(y2 - y1) / static_cast<double>(x2 - x1);
        int dx = abs(x2 - x1);
        int sx = x1 < x2 ? 1 : -1;
        int dy = -abs(y2 - y1);
        int sy = y1 < y2 ? 1 : -1;
//        std::cout << m << ", " << sx << ", " << sy << ": " << x1 << ", " << y1 << ", " << x2 << ", " << y2 << '\n';
        int newX = 0, newY = 0;

        while (true) {
            drawAtSafe(x1 + newX, y1 + newY, 0, 255, 0);

            if (x1 + newX == x2 && y1 + newY == y2) break;
            double a = newX;
            double b = newY + sy;
            double c = newX + sx;
            double d = newY;
//            double a = x1;
//            double b = y1 + sy;
//            double c = x1 + sx;
//            double d = y1;

            double f = abs(b - m * a);
            double g = abs(d - m * c);

            if (dx == 0) {
                newY += sy;
            } else {
                if (f < g) {
                    newY += sy;
                } else {
                    newX += sx;
                }
            }
//            std::cout << x1 + newX << ", " << y1 + newY << '\n';
//            if (abs(y1 + sy - (dy / dx * x1)) < abs(y1 - (dy / dx * (x1 + sx)))) {
//                y1 += sy;
//            } else {
//                x1 += sx;
//            }
        }
    }

//    void drawLine(int x1, int y1, int x2, int y2) {
//        int dx = abs(x2 - x1);
//        int sx = x1 < x2 ? 1 : -1;
//        int dy = -abs(y2 - y1);
//        int sy = y1 < y2 ? 1 : -1;
//        int err = dx + dy;
//        int e2;
//
//        while (true) {
//            drawAtSafe(x1, y1, 0, 255, 0);
//
//            if (x1 == x2 && y1 == y2) break;
//            e2 = 2 * err;
//            if (e2 >= dy) {
//                err += dy;
//                x1 += sx;
//            }
//            if (e2 <= dx) {
//                err += dx;
//                y1 += sy;
//            }
//        }
//    }

    /* DEPRECATED
    void drawSquare(WireFrame square) {
        double a = (w / 2.0) / (tan(FOV * M_PI / 360));
        double xShift = (square.topLeft[0] * square.topLeft[2]) / (a + square.topLeft[0]);
        int projectedX = square.topLeft[0] + xShift;
        drawLine(square.topLeft[0], square.topLeft[1], square.topRight[0], square.topRight[1]);
        drawLine(square.topRight[0], square.topRight[1], square.botRight[0], square.botRight[1]);
        drawLine(square.botRight[0], square.botRight[1], square.botLeft[0], square.botLeft[1]);
        drawLine(square.botLeft[0], square.botLeft[1], square.topLeft[0], square.topLeft[1]);
    }*/

    void drawCube(WireFrame cube) {
        double midX = (w / 2.0);
        double midY = (h / 2.0);
        double aX = (w / 2.0) / (tan(FOV * M_PI / 360.0));
        double aY = (h / 2.0) / (tan(FOV * M_PI / 360.0));
        std::array<std::array<int, 2>, 8> projected = {};
        for (int i = 0; i < 8; i++) {
            // cube.coordinates[i][0] -= midX;
            // cube.coordinates[i][1] -= midY;

            double xShift, yShift;
            int projectedX = -1, projectedY = -1;
            if (cube.coordinates[i][2] > 0) {
                cube.coordinates[i][0] -= midX;
                cube.coordinates[i][1] -= midY;

                xShift = cube.coordinates[i][0] * (cube.coordinates[i][2] - aX) / cube.coordinates[i][2];
                yShift = cube.coordinates[i][1] * (cube.coordinates[i][2] - aY) / cube.coordinates[i][2];

                cube.coordinates[i][0] += midX;
                cube.coordinates[i][1] += midY;

                projectedX = (cube.coordinates[i][0] < midX) ? cube.coordinates[i][0] + xShift : cube.coordinates[i][0] - xShift;
                projectedY = (cube.coordinates[i][1] < midY) ? cube.coordinates[i][1] + yShift : cube.coordinates[i][1] - yShift;
            }
            // double xShift = (cube.coordinates[i][0] * cube.coordinates[i][2]) / (aX + cube.coordinates[i][2]);
            // double yShift = (cube.coordinates[i][1] * cube.coordinates[i][2]) / (aY + cube.coordinates[i][2]);

            // cube.coordinates[i][0] += midX;
            // cube.coordinates[i][1] += midY;

            // int projectedX = cube.coordinates[i][0] + xShift;
            // int projectedY = cube.coordinates[i][1] + yShift;

            // projectedX = (cube.coordinates[i][0] < midX) ? cube.coordinates[i][0] + xShift : cube.coordinates[i][0] - xShift;
            // projectedY = (cube.coordinates[i][1] < midY) ? cube.coordinates[i][1] + yShift : cube.coordinates[i][1] - yShift;

            projected[i] = {projectedX, projectedY};
        }

        // (cube.coordinates[i][0] < midX) ? cube.coordinates[i][0] + xShift :
        // (cube.coordinates[i][1] < midY) ? cube.coordinates[i][1] + yShift :
        drawLine(projected[0][0], projected[0][1], projected[1][0], projected[1][1]);
        drawLine(projected[1][0], projected[1][1], projected[2][0], projected[2][1]);
        drawLine(projected[2][0], projected[2][1], projected[3][0], projected[3][1]);
        drawLine(projected[3][0], projected[3][1], projected[0][0], projected[0][1]);
        drawLine(projected[4][0], projected[4][1], projected[5][0], projected[5][1]);
        drawLine(projected[5][0], projected[5][1], projected[6][0], projected[6][1]);
        drawLine(projected[6][0], projected[6][1], projected[7][0], projected[7][1]);
        drawLine(projected[7][0], projected[7][1], projected[4][0], projected[4][1]);

        drawLine(projected[0][0], projected[0][1], projected[7][0], projected[7][1]);
        drawLine(projected[3][0], projected[3][1], projected[4][0], projected[4][1]);
        drawLine(projected[2][0], projected[2][1], projected[5][0], projected[5][1]);
        drawLine(projected[1][0], projected[1][1], projected[6][0], projected[6][1]);
    }
};

void resetWindowBuffer(GameWindowBuffer* gameWindowBuffer, BITMAPINFO* bitmapInfo, HWND hwnd);

#endif //FINALPROJECT_GAMEWINDOWBUFFER_H
