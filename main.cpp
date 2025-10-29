#include <windows.h>
#include <iostream>
#include "extra/WireFrame.h"

int main() {
    coord topLeft(3, -4, 5);
    coord botRight(4, 6, 1);
    WireFrame square = WireFrame(topLeft, botRight);
    std::cout << square;
    square.rotate(rotateX | rotateY);
    std::cout << square;
}

//// 1. Window Procedure
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    switch (uMsg)
//    {
//        case WM_CLOSE:
//            DestroyWindow(hwnd);
//            break;
//        case WM_DESTROY:
//            PostQuitMessage(0);
//            break;
//        default:
//            return DefWindowProc(hwnd, uMsg, wParam, lParam);
//    }
//    return 0;
//}
//
//// Entry point for the application
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//    // 2. Register the Window Class
//    WNDCLASSEX wc = {0};
//    wc.cbSize = sizeof(WNDCLASSEX);
//    wc.lpfnWndProc = WindowProc;
//    wc.hInstance = hInstance;
//    wc.lpszClassName = "MyWindowClass";
//    RegisterClassEx(&wc);
//
//    // 3. Create the Window
//    HWND m_hwnd = CreateWindowEx(
//            0,                              // Optional window styles
//            "MyWindowClass",               // Class name
//            "My First Win32 Window",       // Window title
//            WS_OVERLAPPEDWINDOW,            // Window style
//            CW_USEDEFAULT, CW_USEDEFAULT,   // Position
//            1920, 1080,                       // Size
//            nullptr,                           // Parent window handle
//            nullptr,                           // Menu handle
//            hInstance,                      // Instance handle
//            nullptr                            // Additional creation data
//            );
//
//    HWND hwndButton = CreateWindow(
//            "BUTTON",  // Predefined class; Unicode assumed
//            "OK",      // Button text
//            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
//            910,         // x position
//            530,         // y position
//            100,        // Button width
//            20,        // Button height
//            m_hwnd,     // Parent window
//            nullptr,    // No menu.
//            (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE),
//            nullptr
//            );
//
//    if (m_hwnd == nullptr)
//    {
//        MessageBox(nullptr, "Window Creation Failed!", "Error", MB_ICONERROR);
//        return 0;
//    }
//
//    // 4. Show and Update the Window
//    ShowWindow(m_hwnd, nCmdShow);
//    UpdateWindow(m_hwnd);
//
//    // 5. Message Loop
//    MSG msg;
//    while (GetMessage(&msg, nullptr, 0, 0))
//    {
//        TranslateMessage(&msg);
//        DispatchMessage(&msg);
//    }
//
//    return (int)msg.wParam;
//}