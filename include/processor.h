#pragma once
#include "queue.h"
#include "data.h"
#include <thread>
#include <atomic>

class Processor {
public:
    Processor(SafeQueue<Position>& in, SafeQueue<Position>& out);

    void start();
    void stop();

private:
    void run();

    std::thread worker;
    SafeQueue<Position>& input;
    SafeQueue<Position>& output;
};