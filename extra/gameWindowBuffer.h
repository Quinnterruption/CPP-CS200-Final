//
// Created by Quinn on 11/1/2025.
//

#ifndef FINALPROJECT_GAMEWINDOWBUFFER_H
#define FINALPROJECT_GAMEWINDOWBUFFER_H
#include <Windows.h>
#include "WireFrame.h"

struct GameWindowBuffer {
    unsigned char* memory = 0;
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
        int dx = abs(x2 - x1);
        int sx = x1 < x2 ? 1 : -1;
        int dy = -abs(y2 - y1);
        int sy = y1 < y2 ? 1 : -1;
        int err = dx + dy;
        int e2;

        while (true) {
            drawAtSafe(x1, y1, 0, 255, 0);

            if (x1 == x2 && y1 == y2) break;
            e2 = 2 * err;
            if (e2 >= dy) {
                err += dy;
                x1 += sx;
            }
            if (e2 <= dx) {
                err += dx;
                y1 += sy;
            }
        }
    }

    void drawSquare(WireFrame square) {
        drawLine(square.topLeft[0], square.topLeft[1], square.topRight[0], square.topRight[1]);
        drawLine(square.topRight[0], square.topRight[1], square.botRight[0], square.botRight[1]);
        drawLine(square.botRight[0], square.botRight[1], square.botLeft[0], square.botLeft[1]);
        drawLine(square.botLeft[0], square.botLeft[1], square.topLeft[0], square.topLeft[1]);
    }
};

void resetWindowBuffer(GameWindowBuffer* gameWindowBuffer, BITMAPINFO* bitmapInfo, HWND hwnd);

#endif //FINALPROJECT_GAMEWINDOWBUFFER_H
