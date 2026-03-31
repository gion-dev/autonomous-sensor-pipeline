#pragma once
#include "components/sensor.h"
#include "components/processor.h"
#include "components/raw_logger.h"
#include "components/filtered_logger.h"

class PipelineManager {
public:
    PipelineManager(const int interval_ms, const double noise, const double alpha);

    void start();
    void stop();

private:
    // TODO Queデータをshared_ptrにしてもいいかも
    SafeQueue<Position> raw_queue;
    SafeQueue<Position> proc_queue;
    SafeQueue<Position> filtered_queue;

    Sensor sensor;
    Processor processor;
    RawLogger raw_logger;
    FilteredLogger filtered_logger;
};