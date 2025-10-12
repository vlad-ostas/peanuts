#pragma once

#include <threadsafe_queue.h>
#include <thread_joiner.h>
#include <functional>

using ThreadTask = std::function<void()>;

class CustomThreadPool
{
public:
    CustomThreadPool();
    ~CustomThreadPool();

    /// @brief Конструктор копирования запрещен
    CustomThreadPool( const CustomThreadPool& ) = delete;
    /// @brief Оператор присваивания запрещен
    CustomThreadPool& operator=( const CustomThreadPool& ) = delete;
    /// @brief Конструктор копирования запрещен
    CustomThreadPool( const CustomThreadPool&& ) = delete;
    /// @brief Оператор присваивания запрещен
    CustomThreadPool& operator=( const CustomThreadPool&& ) = delete;

    void Pause();
    void Resume();

    template <typename TaskType>
    void AddTask( TaskType task )
    {
        workQueue_.Push( ThreadTask( task ) );
    }

private:
    // Возможно стоит передевать callback для возвращение данных или о статусе выполнениея таски
    void WorkerThread();

    std::atomic_bool stopFlag_;
    std::atomic_bool workPaused_;
    std::mutex mutex_;
    std::condition_variable condVar;

    // @note: Порядок очень важен для вызовов dtor
    // В случае thread_pool мы не ждем в dtor а отдаем порядок вызовов на откуп мемберов
    // Что бы все работало правильно, необходимо соблюдать правила
    // сначало должне быть вызван dtor -> joiner
    // далее вызывается dtor -> threads
    // и в конце должен вызваться dtor - queue
    // в таком случаем мы не потеряем данные, так как вызов dtor joiner блокирует вызовы
    // двух других dtor до того как все потоки станут join
    // TODO: Альтернатива для этой констркуции, это прописать в joiner доп функцию которую можно будет вызывать в dtor
    // в таком случае мы будем блокировать окончание scope dtor thread_pool до того как все потоки join
    // следовательно до того как потоки не завершаться выгрузки ресурсов совершено не будет
    ThreadSafeQueue<ThreadTask> workQueue_; ///< [3]
    std::vector<std::thread> threads_;      ///< [2]
    ThreadJoiner joiner_;                   ///< [1] RAII для join потоков
};
