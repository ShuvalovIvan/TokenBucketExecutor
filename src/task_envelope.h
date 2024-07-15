#pragma once
#include "executor.h"

namespace tbe {
    class TaskEnvelope {
    private:
        Task task;
        TaskProperties properties;
    public:
        TaskEnvelope(Task&& task, TaskProperties&& properties) : task(task), properties(properties) {}
        void run(){ task();}
    };
}