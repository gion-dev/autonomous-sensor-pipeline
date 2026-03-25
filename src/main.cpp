#include <iostream>

#include "config.h"
#include "pipeline_manager.h"

int main(int argc, char* argv[]) {
    Config config;

    // TODO ここの処理は別メソッドで切り出したい
    // 実行時に入力した設定値を反映する
    for (int i{1}; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--duration" && (i + 1) < argc) {
            try {
                config.duration_sec = std::stoi(argv[++i]);
            } catch(const std::exception& e) {
                std::cerr << "Invalid duration value : " << e.what() << std::endl;
            }
        } else if (arg == "--interval" && (i + 1) < argc) {
            try {
                config.sensor_interval_ms = std::stoi(argv[++i]);
            } catch(const std::exception& e) {
                std::cerr << "Invalid interval value : " << e.what() << std::endl;
            }
        } else if (arg == "--noise" && (i + 1) < argc) {
            try {
                config.noise_stddev = std::stod(argv[++i]);
            } catch(const std::exception& e) {
                std::cerr << "Invalid noise value : " << e.what() << std::endl;
            }
        } else {
            std::cerr << "Unknown or invalid argument: " << arg << std::endl;
        }
    }
    std::cout << "duration=" << config.duration_sec << std::endl;
    std::cout << "interval=" << config.sensor_interval_ms << std::endl;
    std::cout << "noise=" << config.noise_stddev << std::endl;

    PipelineManager manager(config);

    manager.start();
    std::this_thread::sleep_for(std::chrono::seconds(config.duration_sec));
    manager.stop();

}
