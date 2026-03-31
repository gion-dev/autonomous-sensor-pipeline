#pragma once
#include "common/queue.h"
#include "common/data.h"
#include "components/sensor.h"
#include <thread>

class RawLogger {
public:
    RawLogger(SafeQueue<Position>& q);
    void start();
    void stop();

private:
    void run();

    SafeQueue<Position>& queue;
    std::thread worker;
};