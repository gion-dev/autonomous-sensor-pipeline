#pragma once
#include "sensor.h"
#include "processor.h"
#include "logger.h"

class PipelineManager {
public:
    PipelineManager();

    void start();
    void stop();

private:
    SafeQueue<Position> q1;
    SafeQueue<Position> q2;

    Sensor sensor;
    Processor processor;
    Logger logger;
};