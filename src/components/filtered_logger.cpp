#include "components/filtered_logger.h"
#include <iostream>
#include <fstream>

FilteredLogger::FilteredLogger(SafeQueue<Position>& q) : filtered_queue(q) {}

void FilteredLogger::start() {
    worker = std::thread(&FilteredLogger::run, this);
}

void FilteredLogger::stop() {
    filtered_queue.close();

    if (worker.joinable()) {
        worker.join();
    }
}

void FilteredLogger::run() {
    std::ofstream file("../data/filtered.csv");
    file << "timestamp,x,y\n";  // ヘッダー

    while (true) {
        auto opt = filtered_queue.pop();

        // queueデータが空になったら終了
        if (!opt.has_value()) {
            break;
        }

        Position p = opt.value();
        file << p.timestamp << ","
             << p.x << ","
             << p.y << "\n";
    }
}