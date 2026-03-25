#include "pipeline_manager.h"

PipelineManager::PipelineManager(const Config& config)
    : sensor(q1, config.sensor_interval_ms, config.noise_stddev),
      processor(q1, q2),
      logger(q2),
      config(config)
{}

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