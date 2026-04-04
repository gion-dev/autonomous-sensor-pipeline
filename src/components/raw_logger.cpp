#include "components/raw_logger.h"
#include <fstream>

RawLogger::RawLogger(SafeQueue<Position>& q) : queue(q) {}

void RawLogger::start() {
    worker = std::thread(&RawLogger::run, this);
}

void RawLogger::stop() {
    queue.close();
    if (worker.joinable()) worker.join();
}

void RawLogger::run() {
    std::ofstream file("data/raw.csv");
    file << "timestamp,x,y\n";  // ヘッダー

    while (true) {
        auto opt = queue.pop();

        // queueデータが空になったら終了
        if (!opt.has_value()) break;

        Position p = opt.value();
        file << p.timestamp << "," << p.x << "," << p.y << "\n";
    }
}