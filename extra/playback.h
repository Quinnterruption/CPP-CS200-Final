//
// File Name: playback.h
// Author: TechSolutions
//
//

#ifndef FINALPROJECT_PLAYBACK_H
#define FINALPROJECT_PLAYBACK_H
#include <vector>
#include <chrono>
#include <fstream>
#include <windef.h>
#include "wireFrame.h"
#include "windowBuffer.h"


class Playback {
    uint64_t startTime;
    uint64_t endTime;
    std::ofstream outFile;
    WireFrame prevWireFrame;
public:
    Playback() = default;

    uint64_t currentTimeMillis();
    void startRecord(int length);
    void endRecord();
    bool recording();
    void update(WireFrame wireFrame);

    void replay(HWND__* hwnd, WindowBuffer& windowBuffer);
};


#endif //FINALPROJECT_PLAYBACK_H