#pragma once
#include "common/queue.h"
#include "common/data.h"
#include "sensor.h"
#include <thread>
#include <atomic>

class TruthLogger {
public:
    TruthLogger(SafeQueue<Position>& q);

    void start();
    void stop();

private:
    void run();

    std::thread worker;
    
    SafeQueue<Position>& queue;
};