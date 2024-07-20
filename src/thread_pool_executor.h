#pragma once
#include "executor.h"
#include <chrono>
#include <stddef.h>
#include <thread_pool/thread_pool.h>

namespace tbe {

class ThreadPoolExecutor : public Executor {
public:
  ThreadPoolExecutor(std::size_t numThreads = 4) : pool(numThreads) {}

  ExecutorError exec(Task &&task, TaskProperties &&properties) override {
    try {
      auto result = pool.enqueue([task = std::move(task)]() { task(); });
      result.valid();
      return ExecutorError::None;
    } catch (const std::exception &e) {
      return ExecutorError::Error;
    }
  }

private:
  dp::thread_pool<std::function<void()>> pool;
};

} // namespace tbe