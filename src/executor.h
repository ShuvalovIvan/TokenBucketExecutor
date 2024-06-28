#include <string>
#include <functional>


namespace tbe {

struct TaskProperties {
  std::string user;
};

using Task = std::function<void()>;

enum class ExecutorError : int16_t {};

class Executor {
public:
  virtual ~Executor() {}

  virtual ExecutorError exec(Task&& task, TaskProperties&& properties) = 0; 
};

}  // namespace tbe