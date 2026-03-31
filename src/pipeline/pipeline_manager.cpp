#include "pipeline/pipeline_manager.h"

PipelineManager::PipelineManager(const int interval_ms, const double noise, const double alpha)
    : raw_queue(),
      proc_queue(),
      filtered_queue(),
      sensor(raw_queue, proc_queue, interval_ms, noise),
      processor(proc_queue, filtered_queue, alpha),
      raw_logger(raw_queue),
      filtered_logger(filtered_queue)
{}

void PipelineManager::start() {
    sensor.start();
    processor.start();
    raw_logger.start();
    filtered_logger.start();
}

void PipelineManager::stop() {
    sensor.stop();
    processor.stop();
    raw_logger.stop();
    filtered_logger.stop();
}