//
// File Name: playback.cpp
// Author: TechSolutions
//
//

#include "playback.h"
#include <fstream>


void Playback::startRecord(int length) {
    time(&startTime);
    endTime = startTime + length;
    std::cout << "Start: " << startTime << " End: " << endTime << '\n';
}

bool Playback::recording() {
    if (time(nullptr) >= endTime) {
        return false;
    }
    return true;
}

void Playback::update(WireFrame wireFrame) {
    if (recording()) {
        std::cout << wireFrame.midPoint << ',' << wireFrame.getRotation() << '\n';
    }
}