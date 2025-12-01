//
// File Name: playback.cpp
// Author: TechSolutions
//
//

#include "playback.h"
#include <fstream>
#include <windows.h>
#include "windowBuffer.h"
#include "wireFrame.h"


uint64_t Playback::currentTimeMillis() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void Playback::startRecord(int duration) {
    using namespace std::chrono;

    int durInMS = duration * 1000;
    outFile.open("../recordings/test.txt");
    if (!outFile.is_open()) std::cout << "Fail\n";
    startTime = currentTimeMillis();
    endTime = startTime + durInMS;
//    outFile << startTime << ',' << durInMS << '\n';
    outFile << durInMS << '\n';

    std::cout << "Start: " << startTime << " Duration: " << durInMS << '\n';
}

void Playback::endRecord() {
    if (outFile.is_open()) outFile.close();
}

bool Playback::recording() {
    using namespace std::chrono;
    if (currentTimeMillis() >= endTime) {
        endRecord();
        return false;
    }
    return true;
}

void Playback::update(WireFrame wireFrame) {
    if (wireFrame != prevWireFrame) {
        outFile << currentTimeMillis() - startTime << ' ' << wireFrame.midPoint - prevWireFrame.midPoint << ' ' << wireFrame.getRotation() << '\n';

        std::cout << wireFrame.midPoint - prevWireFrame.midPoint << ' ' << wireFrame.getRotation() << '\n';
    }
    prevWireFrame = wireFrame;
}

void Playback::replay(HWND hwnd, WindowBuffer& windowBuffer) {
    std::ifstream inFile("../recordings/test.txt");
    uint64_t startingTime = currentTimeMillis();

    std::string input;
    std::getline(inFile, input);
    uint64_t endingTime = startingTime + std::stoi(input);

    std::getline(inFile, input);
    int startingRotation = input.back() - '0';
    std::cout << startingRotation << '\n';
    int firstSpace = input.find(' ') + 1;
    int secondSpace = input.find(' ', firstSpace);
    input = input.substr(firstSpace, secondSpace - firstSpace);
    double x = std::stoi(input.substr(0, input.find(',')));
    input = input.substr(input.find(',') + 1);
    double y = std::stoi(input.substr(0, input.find(',')));
    input = input.substr(input.find(',') + 1);
    double z = std::stoi(input.substr(0, input.find(',')));
    input = input.substr(input.find(',') + 1);
    coord startingMidpoint = {x, y, z};
    std::cout << startingMidpoint << '\n';
    WireFrame cube(startingMidpoint, 100, 100, 100);
    cube.setRotation(startingRotation);

    std::getline(inFile, input);
    while (currentTimeMillis() < endingTime) {
        windowBuffer.clear();

        windowBuffer.drawCube(cube);
        cube.rotate();


        // KEEP AT THE END
        if (currentTimeMillis() - startingTime >= std::stoi(input.substr(0, input.find(' ')))) {
            firstSpace = input.find(' ') + 1;
            secondSpace = input.find(' ', firstSpace);
            std::string changeStr = input.substr(firstSpace, secondSpace - firstSpace);
            x = std::stoi(changeStr.substr(0, changeStr.find(',')));
            changeStr = changeStr.substr(changeStr.find(',') + 1);
            y = std::stoi(changeStr.substr(0, changeStr.find(',')));
            changeStr = changeStr.substr(changeStr.find(',') + 1);
            z = std::stoi(changeStr.substr(0, changeStr.find(',')));
            coord change = {x, y, z};
            cube.updateLocation(change);
            cube.setRotation(input.back() - '0');
            std::getline(inFile, input);
        }
        SendMessage(hwnd, WM_PAINT, 0, 0);
    }
//
//    inFile >> input;
//
//
//    while (currentTimeMillis() < endingTime) {
//        windowBuffer.clear();
//
//
//        SendMessage(hwnd, WM_PAINT, 0, 0);
//    }
}