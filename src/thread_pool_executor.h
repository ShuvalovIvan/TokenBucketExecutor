#include <thread_pool/thread_pool.h>
#include "executor.h"
#pragma once

namespace tbe {

    class ThreadPoolExecutor : public Executor {
    public:
        ThreadPoolExecutor(size_t numThreads = 4) : pool(numThreads) {}

        ExecutorError exec(Task&& task, TaskProperties&& properties) override {
            try {
                pool.enqueue([task = std::move(task)]() { task(); });
                return ExecutorError::None;
            } catch (const std::exception& e) {
                return ExecutorError::Error; 
            }
        }

    private:
        dp::thread_pool<std::function<void()>> pool;   
    };

}