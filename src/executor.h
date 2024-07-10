#pragma once
#include <string>
#include <functional>


namespace tbe {

  struct TaskProperties {
    std::string user;
  };

  using Task = std::function<void()>;

  enum class ExecutorError : int16_t {
    None = 0,
    Error = -1
  };

  class Executor {
  public:
    virtual ~Executor() {}

    virtual ExecutorError exec(Task&& task, TaskProperties&& properties) = 0; 
  };


  class InlineExecutor : public Executor {
  public:
    ExecutorError exec(Task&& task, TaskProperties&& properties) override {
      task();
      return ExecutorError::None;
    }
  };

}  // namespace tbe