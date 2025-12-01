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
    using std::string, std::to_string;

    time_t timestamp = time(nullptr);
    tm date = *localtime(&timestamp);

    string fileName = std::format("{}-{}-{}_{}-{}-{}",
        date.tm_mon, date.tm_mday, date.tm_year + 1900, date.tm_hour, date.tm_min, date.tm_sec);

    startRecord(fileName, duration);
}

void Playback::startRecord(const std::string& name, int duration) {
    using namespace std::chrono;

    int durInMS = duration * 1000;
    outFile.open("../recordings/" + name + ".rndr");
    if (!outFile.is_open()) std::cout << "Fail\n";
    startTime = currentTimeMillis();
    endTime = startTime + durInMS;
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

void Playback::replay(HWND hwnd, WindowBuffer& windowBuffer, const std::string& filePath) {
    if (filePath.empty()) return;
    if (filePath.substr(filePath.length() - 6, 5) != ".rndr") return;

    std::ifstream inFile;
    int startOfFileName = filePath.find_last_of('\\') + 1;
    std::string name = filePath.substr(startOfFileName, filePath.length() - startOfFileName - 1);
    std::cout << name << '\n';
    inFile.open("../recordings/" + name);

    if (!inFile.is_open()) return;

    uint64_t startingTime = currentTimeMillis();

    std::string input;
    std::getline(inFile, input);
    uint64_t endingTime = startingTime + std::stoi(input);

    std::getline(inFile, input);
    int startingRotation = input.back() - '0';
    std::cout << startingRotation << '\n';

    int firstSpace = input.find(' ') + 1;
    int secondSpace = input.find(' ', firstSpace);
    std::string coordStr = input.substr(firstSpace, secondSpace - firstSpace);
    coord startingMidpoint = coord::stoc(coordStr);

    std::cout << startingMidpoint << '\n';
    WireFrame cube(startingMidpoint - coord{50, 50, 50}, 100, 100, 100);
    cube.setRotation(startingRotation);

    std::getline(inFile, input);
    while (currentTimeMillis() < endingTime) {
        windowBuffer.clear();

        windowBuffer.drawCube(cube);
        cube.rotate();


        // KEEP AT THE END
        if (input.empty()) break;
        if (currentTimeMillis() - startingTime >= std::stoi(input.substr(0, input.find(' ')))) {
            firstSpace = input.find(' ') + 1;
            secondSpace = input.find(' ', firstSpace);
            std::string changeStr = input.substr(firstSpace, secondSpace - firstSpace);
            coord change = coord::stoc(changeStr);
            cube.updateLocation(change);
            cube.setRotation(input.back() - '0');
            std::getline(inFile, input);
        }
        SendMessage(hwnd, WM_PAINT, 0, 0);
    }
}

// void Playback::replay(HWND hwnd, WindowBuffer& windowBuffer) {
//     std::string name = "11-1-2025_13-20-3";
//     std::ifstream inFile("../recordings/" + name + ".rndr");
//     uint64_t startingTime = currentTimeMillis();
//
//     std::string input;
//     std::getline(inFile, input);
//     uint64_t endingTime = startingTime + std::stoi(input);
//
//     std::getline(inFile, input);
//     int startingRotation = input.back() - '0';
//     std::cout << startingRotation << '\n';
//
//     int firstSpace = input.find(' ') + 1;
//     int secondSpace = input.find(' ', firstSpace);
//     std::string coordStr = input.substr(firstSpace, secondSpace - firstSpace);
//     coord startingMidpoint = coord::stoc(coordStr);
//
//     std::cout << startingMidpoint << '\n';
//     WireFrame cube(startingMidpoint - coord{50, 50, 50}, 100, 100, 100);
//     cube.setRotation(startingRotation);
//
//     std::getline(inFile, input);
//     while (currentTimeMillis() < endingTime) {
//         windowBuffer.clear();
//
//         windowBuffer.drawCube(cube);
//         cube.rotate();
//
//
//         // KEEP AT THE END
//         if (input.empty()) break;
//         if (currentTimeMillis() - startingTime >= std::stoi(input.substr(0, input.find(' ')))) {
//             firstSpace = input.find(' ') + 1;
//             secondSpace = input.find(' ', firstSpace);
//             std::string changeStr = input.substr(firstSpace, secondSpace - firstSpace);
//             coord change = coord::stoc(changeStr);
//             cube.updateLocation(change);
//             cube.setRotation(input.back() - '0');
//             std::getline(inFile, input);
//         }
//         SendMessage(hwnd, WM_PAINT, 0, 0);
//     }
// }