#ifndef BLOCKING_QUEUE_HPP
#define BLOCKING_QUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T>
class BlockingQueue {
   private:
    std::queue<T> queue_;              // Очередь
    std::mutex mutex_;                 // Мьютекс для синхронизациии доступа к очереди
    std::condition_variable condVar_;  // Условная переменная для уведомления потоков
    bool finished_ = false;            // Флаг завершения работы (будут ли в очереди еще элементы)

   public:
    BlockingQueue() = default;
    ~BlockingQueue() = default;

    // Запрет на копирование для безопасности
    BlockingQueue(const BlockingQueue&);
    BlockingQueue& operator=(const BlockingQueue&);

    // Добавляет элемент в очередь и "будит" один из ожидающих потоков
    void push(const T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(item);
        condVar_.notify_one();  // Уведомляем один из ожидающих потоков о добавлении элемента
    }

    // Извлекает элемент из очереди, если она не пуста и работа еще не завершена
    bool pop(T& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        // Захватывает unique_lock и ждет пока очередь не пополнится либо работа не завершится, тем
        // самым блокируя поток
        condVar_.wait(lock, [this] { return !queue_.empty() || finished_; });

        if (queue_.empty() && finished_) return false;

        // Извлекаем элемент и удаляем его из очереди
        item = queue_.front();
        queue_.pop();
        return true;
    }

    // Завершает работу (уведомляет (пробуждает) потоки, что элементов в очереди больше не будет)
    void finish() {
        std::lock_guard<std::mutex> lock(mutex_);
        finished_ = true;
        condVar_.notify_all();
    }
};

#endif  // BLOCKING_QUEUE_HPP
