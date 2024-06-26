#include <gtest/gtest.h>

#include "executor.h"
#include "thread_pool_executor.h"

namespace tbe {


class InlineExecutorTest : public ::testing::Test {
protected:
    InlineExecutor executor;
};


TEST_F(InlineExecutorTest, ExecutesTask) {
    bool taskExecuted = false;
    Task task = [&taskExecuted]() {
      taskExecuted = true;
    };
    TaskProperties properties = {"test_user"};

    executor.exec(std::move(task), std::move(properties));

    EXPECT_TRUE(taskExecuted);
}


TEST_F(InlineExecutorTest, ReturnsNoError) {
    int value = 0;
    Task task = [&value]() {value = 1;};
    TaskProperties properties = {"test_user"};

    ExecutorError error = executor.exec(std::move(task), std::move(properties));

    EXPECT_EQ(error, ExecutorError::None);
    ASSERT_EQ(value, 1);
}


class ThreadPoolExecutorTest : public ::testing::Test {
protected:
    ThreadPoolExecutor executor{6}; 
};

// Test to ensure the task is executed
TEST_F(ThreadPoolExecutorTest, ExecutesTask) {
    std::atomic<bool> taskExecuted{false};
    Task task = [&taskExecuted]() {
        taskExecuted = true;
    };
    TaskProperties properties = {"test_user"};

    executor.exec(std::move(task), std::move(properties));

    for (int i = 0; i < 100; ++i) {
        if (taskExecuted.load()) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    EXPECT_TRUE(taskExecuted);
}


TEST_F(ThreadPoolExecutorTest, ReturnsNoError) {
    Task task = []() {};
    TaskProperties properties = {"test_user"};

    ExecutorError error = executor.exec(std::move(task), std::move(properties));

    EXPECT_EQ(error, ExecutorError::None);
}


} 





int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}