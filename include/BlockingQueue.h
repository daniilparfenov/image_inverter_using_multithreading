#ifndef BLOCKING_QUEUE_HPP
#define BLOCKING_QUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T>
class BlockingQueue {
   private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable condVar_;
    bool finished_ = false;

   public:
    BlockingQueue() = default;
    ~BlockingQueue() = default;

    BlockingQueue(const BlockingQueue&);
    BlockingQueue& operator=(const BlockingQueue&);

    void push(const T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(item);
        condVar_.notify_one();
    }

    bool pop(T& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        condVar_.wait(lock, [this] { return !queue_.empty() || finished_; });

        if (queue_.empty() && finished_) return false;

        item = queue_.front();
        queue_.pop();
        return true;
    }

    void finish() {
        std::lock_guard<std::mutex> lock(mutex_);
        finished_ = true;
        condVar_.notify_all();
    }
};

#endif  // BLOCKING_QUEUE_HPP
