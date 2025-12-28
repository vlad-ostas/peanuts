#pragma once

#include <iostream>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

/// @todo в будущем добавить ограничение в виде type_traits (copyable,
/// copycontstructible, moveconstructible etc.)
template <typename T> class ThreadSafeQueue {
public:
  ThreadSafeQueue() = default;

  /// @brief Конструктор копирования запрещен
  ThreadSafeQueue(const ThreadSafeQueue &) = delete;
  /// @brief Оператор присваивания запрещен
  ThreadSafeQueue &operator=(const ThreadSafeQueue &) = delete;
  /// @brief Конструктор копирования запрещен
  ThreadSafeQueue(const ThreadSafeQueue &&) = delete;
  /// @brief Оператор присваивания запрещен
  ThreadSafeQueue &operator=(const ThreadSafeQueue &&) = delete;

  //
  ~ThreadSafeQueue() { EnableForceSkipWait(); }

  void Push(T new_value) {
    // lock guard is enough
    std::lock_guard lock(mtx);
    data.push(new_value);
    condVar.notify_one();
  }

  bool WaitAndPop(T &value) {
    // uniq lock for wait
    std::unique_lock lock(mtx);
    condVar.wait(lock, [this] { return !data.empty() || skipWait; });
    if (skipWait) {
      return false;
    }
    value = data.front();
    data.pop();
    return true;
  }

  /// @note опасно использовать, т.к. существует возможность быть
  /// заблокированным на wait для большей безотказности лучше все использовать
  /// TryPop так как он все таки не использует wait ожидане пополнения задач
  /// приятная фича но нужно обдумать варианты как обобйти блокировку Пример
  /// блокировки: Ожидаем задачи в отдельном потоке В этот момент вызывается
  /// дестркутор потока для потока вызывается join() так как вы находимся в wait
  /// то join никогда не выполнится вызывать какой то notify извне мы не можем,
  /// следовательно будет блокировка из которой нельзя будет выйти
  std::shared_ptr<T> WaitAndPop() {
    // uniq lock for wait
    std::unique_lock lock(mtx);
    /// @todo: может быть lock, когды вызываем dtr
    /// можем находится все еще в ожидании
    /// Предусмотреть такую ситуацию в destructor
    condVar.wait(lock, [this] { return !data.empty() || skipWait; });
    if (skipWait) {
      return nullptr;
    }
    std::shared_ptr<T> value(std::make_shared<T>(data.front()));
    // pop after потому что может вылететь ошибка во время make_shared и pop не
    // произойдет так мы хотя бы не потеряем данные
    data.pop();
    return value;
  }

  bool TryPop(T &value) {
    std::lock_guard lock(mtx);
    if (data.empty()) {
      return false;
    }
    value = data.front();
    data.pop();
    return true;
  }

  std::shared_ptr<T> TryPop() {
    std::lock_guard lock(mtx);
    if (data.empty()) {
      return nullptr;
    }
    std::shared_ptr<T> value(std::make_shared<T>(data.front()));
    data.pop();
    return value;
  }

  // необходимые функции для Wait
  void EnableForceSkipWait() {
    std::cout << "ForceSkipWait = Enabled" << std::endl;
    std::lock_guard lock(mtx);
    skipWait = true;
    condVar.notify_all();
  }

  // необходимые функции для Wait
  void DisableForceSkipWait() {
    std::cout << "ForceSkipWait = Disabled" << std::endl;
    std::lock_guard lock(mtx);
    skipWait = false;
    condVar.notify_all();
  }

  bool IsEmpty() const {
    std::lock_guard lock(mtx);
    return data.empty();
  }

private:
  bool skipWait = false;
  std::condition_variable condVar;
  std::queue<T> data;
  mutable std::mutex mtx;
};
