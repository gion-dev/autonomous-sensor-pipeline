#pragma once
#include "common/queue.h"
#include "common/data.h"
#include "sensor.h"
#include <thread>
#include <atomic>

class FilteredLogger {
public:
    FilteredLogger(SafeQueue<Position>& q);

    void start();
    void stop();

private:
    void run();

    std::thread worker;
    
    SafeQueue<Position>& filtered_queue;
};