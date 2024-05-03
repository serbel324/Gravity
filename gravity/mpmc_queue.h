#pragma once

#include <deque>
#include <mutex>
#include <optional>

template <class T>
class MutexMPMCQueue {
public:
    MutexMPMCQueue() {
    }

    MutexMPMCQueue(size_t) {
    }

public:
    void push(T elem) {
        std::lock_guard guard(_mtx);
        _queue.push_back(std::move(elem));
    }

    void pop(T& elem) {
        std::lock_guard guard(_mtx);
        elem = std::move(_queue.front());
        _queue.pop_front();
    }

    size_t size() {
        std::lock_guard guard(_mtx);
        return _queue.size();
    }

private:
    std::deque<T> _queue;
    std::mutex _mtx;
};
