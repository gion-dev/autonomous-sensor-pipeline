#pragma once
#include "common/queue.h"
#include "common/data.h"
#include <thread>
#include <atomic>

class Sensor {
public:
    Sensor(SafeQueue<Position>& raw, SafeQueue<Position>& proc, int interval_ms, double noise_stddev);

    void start();
    void stop();
    
private:
    void run();

    std::thread worker;
    std::atomic<bool> sensorRunning{false};
    
    SafeQueue<Position>& raw_queue;
    SafeQueue<Position>& proc_queue;

    int interval;
    double noise_stddev;
};