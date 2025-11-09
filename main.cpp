#include <windows.h>
#include <iostream>
#include "resources/resource.h"
#include "extra/WireFrame.h"
#include "extra/gameWindowBuffer.h"

struct WindowStuff {
    bool running = true;

    BITMAPINFO bitmapInfo = {};
    GameWindowBuffer gameWindowBuffer = {};
};

WindowStuff windowStuff;
RECT rect = {};

int width, height;
const char g_szClassName[] = "myWindowClass";
coord topLeft = {300, 400, 500};
coord botRight = {400, 600, 100};

double xOne = 700;
double xTwo = xOne + 100;
double yOne = 400;
double yTwo = yOne + 100;
double dist1 = 100;
double dist2 = dist1 + 100;

coord topFrontLeft = {xOne, yOne, dist1};
coord topFrontRight = {xTwo, yOne, dist1};
coord topBackRight = {xTwo, yOne, dist2};
coord topBackLeft = {xOne, yOne, dist2};
coord botBackLeft = {xOne, yTwo, dist2};
coord botBackRight = {xTwo, yTwo, dist2};
coord botFrontRight = {xTwo, yTwo, dist1};
coord botFrontLeft = {xOne, yTwo, dist1};
//WireFrame square = WireFrame(topLeft, botRight);
WireFrame cube = WireFrame({topFrontLeft, topFrontRight, topBackRight, topBackLeft, botBackLeft, botBackRight, botFrontRight, botFrontLeft});
WireFrame cube2 = WireFrame(topFrontLeft, 100, 100, 100);

void onIdle(int w, int h, GameWindowBuffer& gameWindowBuffer) {
    gameWindowBuffer.clear();

//    for (int i = 0; i < gameWindowBuffer.w; i++) {
//        for (int j = 0; j < gameWindowBuffer.h; j++) {
//            gameWindowBuffer.drawAtSafe(i, j, i % 256, j % 256, (i * j) % 256);
//        }
//    }

//    gameWindowBuffer.drawSquare(square);
//    gameWindowBuffer.drawCube(cube);
    gameWindowBuffer.drawCube(cube2);
//    cube2.rotate(rotateX | rotateY | rotateZ);
//    cube.rotate(rotateZ | rotateY | rotateX);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_SIZE: {
            GetClientRect(hwnd, &rect);
            height = rect.bottom;
            width = rect.right;
            resetWindowBuffer(&windowStuff.gameWindowBuffer, &windowStuff.bitmapInfo, hwnd);
            break;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC DeviceContext = BeginPaint(hwnd, &ps);

            HDC hdc = GetDC(hwnd);

            StretchDIBits(hdc,
                          0, 0, windowStuff.gameWindowBuffer.w, windowStuff.gameWindowBuffer.h,
                          0, 0, windowStuff.gameWindowBuffer.w, windowStuff.gameWindowBuffer.h,
                          windowStuff.gameWindowBuffer.memory,
                          &windowStuff.bitmapInfo,
                          DIB_RGB_COLORS,
                          SRCCOPY
                          );

            ReleaseDC(hwnd, hdc);

            EndPaint(hwnd, &ps);
            break;
        }
        /* Doesn't Work Right
         */
//        case WM_CREATE: {
//            HMENU hMenu, hSubMenu;
//            HICON hIcon, hIconSm;
//
//            hMenu = CreateMenu();
//            AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "E&xit");
//            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");
//
//            hSubMenu = CreatePopupMenu();
//            AppendMenu(hSubMenu, MF_STRING, ID_STUFF_GO, "&Go");
//            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Stuff");
//
//            SetMenu(hwnd, hMenu);
//
//            hIcon = LoadImage(NULL, "menu_two.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
//            if (hIcon) {
//                SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
//            } else {
//                MessageBox(hwnd, "Could not load large icon!", "Error", MB_OK | MB_ICONERROR);
//            }
//
//            hIconSm = LoadImage(NULL, "menu_two.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
//            if (hIconSm) {
//                SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
//            } else {
//                MessageBox(hwnd, "Could not load small icon!", "Error", MB_OK | MB_ICONERROR);
//            }
//            break;
//        }
        case WM_COMMAND:
            switch(LOWORD(wParam)) {
                case ID_FILE_EXIT:
//                    square.updateLocation({-10, -10, -10});
                    break;
                case ID_STUFF_GO:
//                    square.updateLocation({10, 10, 10});
                    break;
            }
            break;
        case WM_RBUTTONDOWN: {
            cube2.updateLocation({0, 0, 10});
            break;
        }
        case WM_LBUTTONDOWN: {
            cube2.updateLocation({0, 0, -10});
//            windowStuff.gameWindowBuffer.clear();
//            windowStuff.gameWindowBuffer.drawCube(cube);
//            cube.rotate(rotateZ);
            break;
        }
        case WM_CLOSE:
            windowStuff.running = false;
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    // Step 1: Register Window Class
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_MYICON));
    wc.hIconSm = (HICON)LoadImage(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_MYICON), IMAGE_ICON, 16, 16, 0);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);
    wc.lpszClassName = g_szClassName;

    if (!RegisterClassEx(&wc)) {
        MessageBox(nullptr, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Create Window
    hwnd = CreateWindowEx(
            WS_EX_CLIENTEDGE,
            g_szClassName,
            "The title of my window",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, 1000, 1000,
            nullptr, nullptr, hInstance, nullptr
            );

    resetWindowBuffer(&windowStuff.gameWindowBuffer, &windowStuff.bitmapInfo, hwnd);

    if (hwnd == nullptr) {
        MessageBox(nullptr, "Window Creation Failed!", "ERROR", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    GetClientRect(hwnd, &rect);
    height = rect.bottom;
    width = rect.right;

    // Step 3: "Game" Loop
    while (windowStuff.running) {
        if (PeekMessage(&Msg, hwnd, 0, 0, PM_REMOVE)) {
            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
        } else {
            onIdle(width, height, windowStuff.gameWindowBuffer);
            SendMessage(hwnd, WM_PAINT, 0, 0);
        }
    }

    return Msg.wParam;
}