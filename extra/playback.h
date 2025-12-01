//
// File Name: playback.h
// Author: TechSolutions
//
//

#ifndef FINALPROJECT_PLAYBACK_H
#define FINALPROJECT_PLAYBACK_H
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

    static uint64_t currentTimeMillis();
    void startRecord(int duration);

    void startRecord(const std::string &name, int duration);

    void endRecord();
    bool recording();
    void update(WireFrame wireFrame);

    void replay(HWND__ *hwnd, WindowBuffer &windowBuffer, const std::string& filePath);
};


#endif //FINALPROJECT_PLAYBACK_H