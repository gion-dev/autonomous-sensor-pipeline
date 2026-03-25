#pragma once

struct Config {
    // デフォルトの設定値
    int duration_sec = 5;
    int sensor_interval_ms = 500;
    double noise_stddev = 0.5;
};