#pragma once
#include <benchmark/benchmark.h>
#include <memory>
#include <latch>
#include <vector>
#include <string>
#include "thread_pool_executor.h" 
#include "../common/test_task.h"

namespace tbe {
    static void BM_ThreadPoolExecutor(benchmark::State& state) {

        ThreadPoolExecutor executor{6};

        std::vector<std::string> users;
        for (int i = 0; i < state.range(0); ++i) {
            users.push_back(std::string("user") + std::to_string(i));
        }
    
        auto latch = std::make_shared<std::latch>(state.iterations());
        int user = 0;
        int per_user_count = 0;
    
        for (auto _ : state) {
            if (per_user_count++ > user) {
                user = (user + 1) % state.range(0);
                per_user_count = 0;
            }
            TaskProperties properties;
            properties.user = users[user];
            // get the test task.
            executor.exec(TestTask::get(latch), std::move(properties));
        }
        latch->wait();
    }
    
    BENCHMARK(BM_ThreadPoolExecutor)->Range(1, 24);
    
}