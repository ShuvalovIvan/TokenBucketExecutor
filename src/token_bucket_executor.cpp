#include "token_bucket_executor.h"

namespace tbe {
    TokenBucketExecutor::TokenBucketExecutor(size_t size) : executor(size), execThreads(size){
        for(int i = 0; i < execThreads; ++i) {
            TaskProperties properties;
            executor.exec([this] -> void {
                while (!termination_flag.load()) {
                    std::cerr<<"Wait for envelope"<<std::endl;
                    auto envelope = queue.pop();
                    envelope.run();
                }
            }, std::move(properties));
        }
    }

    ExecutorError TokenBucketExecutor::exec(Task&& task, TaskProperties&& properties) {
        queue.push(std::move(task), std::move(properties)); 
    }

    void TokenBucketExecutor::terminate() {
        termination_flag.store(true, std::memory_order_relaxed);
    }
}