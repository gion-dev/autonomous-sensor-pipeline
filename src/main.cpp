#include "pipeline_manager.h"

int main() {
    PipelineManager pipeline;

    pipeline.start();

    std::this_thread::sleep_for(std::chrono::seconds(5));

    pipeline.stop();

    return 0;
}