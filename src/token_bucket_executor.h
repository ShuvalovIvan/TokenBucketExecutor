#pragma once
#include "thread_pool_executor.h"
#include "token_bucket_queue.h"
#include "task_envelope.h"


namespace tbe {
    class TokenBucketExecutor : public Executor {
    private:
        ThreadPoolExecutor executor;
        TokenBucketQueue queue;
        std::size_t execThreads;
        std::atomic<bool> termination_flag;
    public:
        TokenBucketExecutor(std::size_t size);
        ExecutorError exec(Task&& task, TaskProperties&& properties) override;
        void terminate();
    };
}
