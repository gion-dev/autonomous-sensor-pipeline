#include "processor.h"

Processor::Processor(SafeQueue<Position>& in, SafeQueue<Position>& out)
    : input(in), output(out) {}

void Processor::start() {
    worker = std::thread(&Processor::run, this);
}

void Processor::stop() {
    input.close();

    if (worker.joinable()) {
        worker.join();
    }
}

void Processor::run() {
    Position prev{0, 0, 0};

    while (true) {
        auto opt = input.pop();

        // queueデータが空になったら終了
        if (!opt.has_value()) {
            break;
        }

        Position curr = opt.value();

        Position filtered;
        filtered.x = (prev.x + curr.x) / 2;
        filtered.y = (prev.y + curr.y) / 2;
        filtered.timestamp = curr.timestamp;

        output.push(filtered);

        prev = curr;
    }
}