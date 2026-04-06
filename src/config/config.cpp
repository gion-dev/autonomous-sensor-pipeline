#include "config/config.h"
#include <iostream>

Config parseArgs(int argc, char* argv[]) {
    Config config;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        try {
            if (arg == "--duration" && (i + 1) < argc) {
                config.duration_sec = std::stoi(argv[++i]);

            } else if (arg == "--interval" && (i + 1) < argc) {
                config.sensor_interval_ms = std::stoi(argv[++i]);

            } else if (arg == "--noise" && (i + 1) < argc) {
                config.noise_stddev = std::stod(argv[++i]);

            } else if (arg == "--alpha" && (i + 1) < argc) {
                config.alpha = std::stod(argv[++i]);

            } else if (arg == "--ax" && (i + 1) < argc) {
                config.ax = std::stod(argv[++i]);

            } else if (arg == "--ay" && (i + 1) < argc) {
                config.ay = std::stod(argv[++i]);

            } else {
                std::cerr << "Unknown argument: " << arg << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Invalid value for " << arg << ": " << e.what() << std::endl;
        }
    }

    std::cout << "duration=" << config.duration_sec << std::endl;
    std::cout << "interval=" << config.sensor_interval_ms << std::endl;
    std::cout << "noise=" << config.noise_stddev << std::endl;
    std::cout << "alpha=" << config.alpha << std::endl;
    std::cout << "acceleration_x=" << config.ax << std::endl;
    std::cout << "acceleration_y=" << config.ay << std::endl;

    return config;
}

void validateConfig(const Config& config) {
    if (config.duration_sec <= 0) {
        throw std::runtime_error("duration must be > 0");
    }
    if (config.sensor_interval_ms <= 0) {
        throw std::runtime_error("interval must be > 0");
    }
    if (config.noise_stddev > 5.0) {
    std::cout << "[WARN] noise is large, result may be unstable" << std::endl;
    }
    if (config.alpha < 0.0 || config.alpha > 1.0) {
        throw std::runtime_error("alpha must be in [0, 1]");
    }
    if (config.ax < -10.0 || config.ax > 10.0) {
        throw std::runtime_error("ax must be in [-10.0, 10.0]");
    }
    if (config.ay < -10.0 || config.ay > 10.0) {
        throw std::runtime_error("ay must be in [-10.0, 10.0]");
    }
}