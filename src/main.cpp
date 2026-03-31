#include <iostream>

#include "config/config.h"
#include "pipeline/pipeline_manager.h"

int main(int argc, char* argv[]) {
    Config config = parseArgs(argc, argv);
    validateConfig(config);

    // 修正したい箇所に関してはTODOで検索する
    // TODO 加速度も入力できるようにする
    // TODO 各ファイルのメンバ変数にmを付ける

    PipelineManager manager(config.sensor_interval_ms, config.noise_stddev, config.alpha);

    manager.start();
    std::this_thread::sleep_for(std::chrono::seconds(config.duration_sec));
    manager.stop();

}
