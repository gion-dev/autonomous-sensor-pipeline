#include "components/truth_logger.h"
#include <fstream>

TruthLogger::TruthLogger(SafeQueue<Position>& q) : queue(q) {}

void TruthLogger::start() {
    worker = std::thread(&TruthLogger::run, this);
}

void TruthLogger::stop() {
    queue.close();
    if (worker.joinable()) worker.join();
}

void TruthLogger::run() {
    std::ofstream file("data/truth.csv");
    file << "timestamp,x,y\n";  // ヘッダー

    while (true) {
        auto opt = queue.pop();

        // queueデータが空になったら終了
        if (!opt.has_value()) break;

        Position p = opt.value();
        file << p.timestamp << "," << p.x << "," << p.y << "\n";
    }
}