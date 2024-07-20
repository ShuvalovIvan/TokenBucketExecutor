#pragma once
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <memory>
#include <iostream>

#include "executor.h"
#include "task_envelope.h"

namespace tbe {
    class TokenBucketQueue {
    private:
        std::queue<TaskEnvelope> m_data;
        std::mutex m_Mutex;
        std::condition_variable m_cv;
        const int m_QueueSize;
        std::atomic_bool m_bFinished;


    public:
        TokenBucketQueue(int MaxQueue = 10) 
            : m_bFinished(false), m_QueueSize(MaxQueue) 
        {}

        void push(Task&& task, TaskProperties&& properties)
        {
            TaskEnvelope envelope(std::move(task), std::move(properties));
            std::unique_lock<std::mutex> lock(m_Mutex);
            m_data.push(envelope);
            m_cv.notify_one();
            std::cerr << "Pushed, q size " << m_data.size() << std::endl;
        }

        TaskEnvelope pop() 
        {
            std::unique_lock<std::mutex> lock(m_Mutex);
            do {
                m_cv.wait(lock, [&](){ 
                    return !m_data.empty() || m_bFinished; 
                }); // predicate an while loop - protection from spurious wakeups
                if (m_bFinished) {
                    return TaskEnvelope([]{}, {});
                }
            } while (m_data.empty());
            auto envelope = m_data.front();
            m_data.pop();
            std::cerr << "Popped, q size " << m_data.size() << std::endl;
            return envelope;
        }

        void terminate()
        {
            std::unique_lock<std::mutex> lock(m_Mutex);
            m_bFinished = true;
            m_cv.notify_all();
        }
    };
}