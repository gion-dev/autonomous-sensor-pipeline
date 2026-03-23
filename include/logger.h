#pragma once
#include "queue.h"
#include "data.h"
#include <thread>
#include <atomic>

class Logger {
public:
    Logger(SafeQueue<Position>& q);

    void start();
    void stop();

private:
    void run();

    std::thread worker;
    SafeQueue<Position>& queue;
};