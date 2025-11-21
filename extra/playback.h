//
// File Name: playback.h
// Author: TechSolutions
//
//

#ifndef FINALPROJECT_PLAYBACK_H
#define FINALPROJECT_PLAYBACK_H
#include <vector>
#include <ctime>
#include "wireFrame.h"


class Playback {
    time_t startTime;
    time_t endTime;
public:
    Playback() = default;

    void startRecord(int length);
    bool recording();
    void update(WireFrame wireFrame);
};


#endif //FINALPROJECT_PLAYBACK_H