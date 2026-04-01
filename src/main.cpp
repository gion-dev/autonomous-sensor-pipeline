#include <iostream>
#include <thread>
#include <chrono>

#include "config/config.h"
#include "pipeline/pipeline_manager.h"

// 進捗表示
static void showProgress(int duration_sec) {
    const int steps = 20;
    int sleep_per_step = duration_sec * 1000 / steps;

    for (int i = 1; i <= steps; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_per_step));

        int percent = i * 5;

        std::cout << "\rProgress: [";
        for (int j = 0; j < steps; ++j) {
            if (j < i) std::cout << "*";
            else std::cout << "-";
        }
        std::cout << "] " << percent << "%" << std::flush;
    }

    std::cout << std::endl;
}

int main(int argc, char* argv[]) {

    // TODO 各ファイルのメンバ変数にmを付ける
    // TODO namespaceを付ける

    // 入力値のチェック
    Config config = parseArgs(argc, argv);
    validateConfig(config);

    PipelineManager manager(
        config.sensor_interval_ms,
        config.noise_stddev,
        config.alpha,
        config.ax,
        config.ay
    );

    // 別スレッドで進捗表示
    std::thread progress_thread(showProgress, config.duration_sec);

    // Pipelineを実行してセンターデータを収集
    manager.start();
    std::this_thread::sleep_for(std::chrono::seconds(config.duration_sec));
    manager.stop();

    // 進捗表示スレッド終了待ち
    progress_thread.join();

    return 0;
}