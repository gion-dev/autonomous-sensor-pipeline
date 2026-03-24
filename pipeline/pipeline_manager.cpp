#include "pipeline_manager.h"

PipelineManager::PipelineManager()
    : sensor(q1), processor(q1, q2), logger(q2) {}

void PipelineManager::start() {
    sensor.start();
    processor.start();
    logger.start();
}

void PipelineManager::stop() {
    logger.stop();
    processor.stop();
    sensor.stop();
}