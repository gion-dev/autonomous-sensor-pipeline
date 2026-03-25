#include "sensor.h"
#include <chrono>
#include <random>

Sensor::Sensor(SafeQueue<Position>& q, int interval_ms, double noise)
    : queue(q), interval(interval_ms), noise_stddev(noise) {}

void Sensor::start() {
    sensorRunning = true;
    worker = std::thread(&Sensor::run, this);
}

void Sensor::stop() {
    sensorRunning = false;
    if (worker.joinable()) {
        worker.join();
    }
}

void Sensor::run() {
    double x = 0.0;
    double y = 0.0;

    std::random_device rd;
    std::mt19937 gen(rd());

    // ノイズを作成、分散は設定値から
    std::normal_distribution<> noise(0.0, noise_stddev);

    while (sensorRunning) {
        Position p;

        // ノイズ付き
        p.x = x + noise(gen);
        p.y = y + noise(gen);

        p.timestamp = std::chrono::system_clock::now().time_since_epoch().count();

        queue.push(p);

        x += 1.0;
        y += 0.5;

        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }
}