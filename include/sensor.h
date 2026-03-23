#pragma once
#include "queue.h"
#include "data.h"
#include <thread>
#include <atomic>

class Sensor {
public:
    Sensor(SafeQueue<Position>& q);

    void start();
    void stop();

private:
    void run();

    std::thread worker;
    std::atomic<bool> sensorRunning{false};
    SafeQueue<Position>& queue;
};