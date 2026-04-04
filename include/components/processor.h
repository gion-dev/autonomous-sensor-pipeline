#pragma once
#include "common/queue.h"
#include "common/data.h"
#include <thread>
#include <atomic>

class Processor {
public:
    Processor(SafeQueue<Position>& in, SafeQueue<Position>& out, const double alpha);

    void start();
    void stop();

private:
    void run();

    std::thread worker;
    
    SafeQueue<Position>& input;
    SafeQueue<Position>& output;
    double alpha;

    bool is_first;
    Position prev;
};