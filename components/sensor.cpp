#include "sensor.h"
#include <chrono>
#include <random>

Sensor::Sensor(SafeQueue<Position>& q) : queue(q) {}

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
    std::normal_distribution<> noise(0.0, 0.5); // 平均0、分散0.5

    while (sensorRunning) {
        Position p;

        // ノイズ付き
        p.x = x + noise(gen);
        p.y = y + noise(gen);

        p.timestamp = std::chrono::system_clock::now().time_since_epoch().count();

        queue.push(p);

        x += 1.0;
        y += 0.5;

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}