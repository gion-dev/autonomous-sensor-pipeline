#include "components/sensor.h"
#include <chrono>
#include <random>

Sensor::Sensor(SafeQueue<Position>& raw, SafeQueue<Position>& proc, int interval_ms, double noise, double ax, double ay)
    : raw_queue(raw), proc_queue(proc), interval(interval_ms), noise_stddev(noise), acceleration_x(ax), acceleration_y(ay) {}

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
    // 位置（状態量）
    double x = 0.0;
    double y = 0.0;

    // 速度（時間積分で更新される）
    double velocity_x = 0.0;
    double velocity_y = 0.0;

    // 前回ループ時刻（dt計算用）
    auto prev_time = std::chrono::steady_clock::now();

    // noise用の乱数データ生成
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> noise(0.0, noise_stddev);

    while (sensorRunning) {
        auto now = std::chrono::steady_clock::now();

        // 経過時間dt（秒）
        double dt = std::chrono::duration<double>(now - prev_time).count();
        prev_time = now;

        // 加速度を時間積分して速度を更新
        velocity_x += acceleration_x * dt;
        velocity_y += acceleration_y * dt;
        
        // 速度を時間積分して位置を更新
        x += velocity_x * dt;
        y += velocity_y * dt;

        // ノイズを加えた観測値を生成（センサ出力を模擬）
        Position p;
        p.x = x + noise(gen);
        p.y = y + noise(gen);

        // タイムスタンプ（ナノ秒）
        p.timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();

        // 生データと処理用データをそれぞれキューへ投入
        raw_queue.push(p);
        proc_queue.push(p);

        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }
}