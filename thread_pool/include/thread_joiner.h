#pragma once

#include <vector>
#include <thread>

class ThreadJoiner {
public:
  explicit ThreadJoiner(std::vector<std::thread> &threads) : threads_(threads) {
    // std::cout << std::format("ThreadJoiner ctor") << std::endl;
  }

    /// @brief Конструктор копирования запрещен
    ThreadJoiner( const ThreadJoiner& ) = delete;
    /// @brief Оператор присваивания запрещен
    ThreadJoiner& operator=( const ThreadJoiner& ) = delete;
    /// @brief Конструктор копирования запрещен
    ThreadJoiner( const ThreadJoiner&& ) = delete;
    /// @brief Оператор присваивания запрещен
    ThreadJoiner& operator=( const ThreadJoiner&& ) = delete;


  ~ThreadJoiner() {
    // LOG_DEBUG( "ThreadJoiner dtor" );
    for (auto &thread : threads_) {
      if (thread.joinable()) {
        thread.join();
      }
    }
  }

private:
  std::vector<std::thread> &threads_;
};
