#pragma once
#include "queue.h"
#include "data.h"
#include <thread>
#include <atomic>

class Sensor {
public:
    Sensor(SafeQueue<Position>& q, int interval_ms, double noise_stddev);

    void start();
    void stop();

private:
    void run();

    int interval;
    double noise_stddev;

    std::thread worker;
    std::atomic<bool> sensorRunning{false};
    SafeQueue<Position>& queue;
};