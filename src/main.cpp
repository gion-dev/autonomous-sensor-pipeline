#include "sensor.h"
#include "processor.h"
#include "logger.h"
#include "queue.h"
#include "data.h"
#include <thread>

int main() {
    SafeQueue<Position> q1;
    SafeQueue<Position> q2;

    Sensor s(q1);
    Processor p(q1, q2);
    Logger l(q2);

    // 起動
    s.start();
    p.start();
    l.start();

    // 5秒動かす
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // 停止
    s.stop();
    p.stop();
    l.stop();

    return 0;
}