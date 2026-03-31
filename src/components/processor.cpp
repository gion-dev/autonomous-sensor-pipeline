#include "components/processor.h"

Processor::Processor(SafeQueue<Position>& in, SafeQueue<Position>& out, const double alpha)
    : input(in), output(out), alpha(alpha) {}

void Processor::start() {
    worker = std::thread(&Processor::run, this);
}

void Processor::stop() {
    input.close();

    if (worker.joinable()) {
        worker.join();
    }
}

bool is_first = true;
Position prev;

void Processor::run() {
    while (true) {
        auto opt = input.pop();

        // queueデータが空になったら終了
        if (!opt.has_value()) {
            break;
        }

        Position curr = opt.value();

        // 初回は過去データが存在しないため、フィルタせずそのまま出力する
        if (is_first) {
            prev = curr;
            is_first = false;
            output.push(curr);
            continue;
        }

        // 指数移動平均（EMA）によるノイズ低減
        // 現在値と前回のフィルタ結果を重み付けして滑らかにする
        Position filtered;
        filtered.x = alpha * curr.x + (1 - alpha) * prev.x;
        filtered.y = alpha * curr.y + (1 - alpha) * prev.y;
        filtered.timestamp = curr.timestamp;

        output.push(filtered);

        prev = filtered;
    }
}