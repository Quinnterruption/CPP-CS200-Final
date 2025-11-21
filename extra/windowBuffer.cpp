//
// Created by Quinn on 11/1/2025.
//

#include "windowBuffer.h"

void resetWindowBuffer(WindowBuffer* windowBuffer, BITMAPINFO* bitmapInfo, HWND hwnd) {
    RECT rect = {};
    GetClientRect(hwnd, &rect);
    windowBuffer->h = rect.bottom;
    windowBuffer->w = rect.right;

    if (windowBuffer->memory) {
        VirtualFree(windowBuffer->memory, 0, MEM_RELEASE);
    }

    windowBuffer->memory = (unsigned char*) VirtualAlloc(0, 4 * windowBuffer->w * windowBuffer->h,
                                                             MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    bitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFO);
    bitmapInfo->bmiHeader.biWidth = windowBuffer->w;
    bitmapInfo->bmiHeader.biHeight = -windowBuffer->h;
    bitmapInfo->bmiHeader.biPlanes = 1;
    bitmapInfo->bmiHeader.biBitCount = 32;
    bitmapInfo->bmiHeader.biCompression = BI_RGB;
}