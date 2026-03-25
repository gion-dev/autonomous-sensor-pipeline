#pragma once
#include "config.h"
#include "sensor.h"
#include "processor.h"
#include "logger.h"

class PipelineManager {
public:
    PipelineManager(const Config& config);

    void start();
    void stop();

private:
    Config config;

    SafeQueue<Position> q1;
    SafeQueue<Position> q2;

    Sensor sensor;
    Processor processor;
    Logger logger;
};