#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

template<typename T>
class SafeQueue {
public:
    void push(T value) {
        std::lock_guard<std::mutex> lock(mtx);
        q.push(value);
        cv.notify_one();
    }

    // 空で返す場合は終了する
    std::optional<T> pop() {
        std::unique_lock<std::mutex> lock(mtx);

        cv.wait(lock, [this]() { return !q.empty() || closed; });

        if (q.empty()) {
            return std::nullopt; // 終了
        }

        T value = q.front();
        q.pop();
        return value;
    }

    // 終了通知（popする処理を持ったクラスのstopでコールする）
    void close() {
        std::lock_guard<std::mutex> lock(mtx);
        closed = true;
        cv.notify_all();
    }

private:
    std::queue<T> q;
    std::mutex mtx;
    std::condition_variable cv;
    bool closed = false;
};