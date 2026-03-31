#pragma once

struct Config {
    int duration_sec = 5;
    int sensor_interval_ms = 500;
    double noise_stddev = 0.5;
    double alpha = 0.3;
};

Config parseArgs(int argc, char* argv[]);
void validateConfig(const Config& config);