#include "logger.h"
#include <iostream>
#include <fstream>

Logger::Logger(SafeQueue<Position>& q) : queue(q) {}

void Logger::start() {
    worker = std::thread(&Logger::run, this);
}

void Logger::stop() {
    queue.close();

    if (worker.joinable()) {
        worker.join();
    }
}

void Logger::run() {
    std::ofstream file("../data/output.csv");

    // ヘッダー
    file << "timestamp,x,y\n";

    while (true) {
        auto opt = queue.pop();

        // queueデータが空になったら終了
        if (!opt.has_value()) {
            break;
        }

        Position p = opt.value();

        file << p.timestamp << ","
             << p.x << ","
             << p.y << std::endl;  // ← flushされる
    }

    file.close();
}