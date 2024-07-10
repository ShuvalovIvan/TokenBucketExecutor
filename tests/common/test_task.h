#pragma once
#include <functional>
#include <memory>
#include <latch>

namespace tbe
{

    class TestTask
    {
    public:
        TestTask(std::weak_ptr<std::latch> latch) : _latch(latch) {}

        static std::function<void()> get(std::weak_ptr<std::latch> latch)
        {
            TestTask t(latch);
            return [t = std::move(t)]() mutable -> void
            {
                t.execute();
            };
        }
        void execute() 
        {
            auto latch = _latch.lock();
            if (latch) 
            {
                latch->count_down();
            }
        }

    private:
        std::weak_ptr<std::latch> _latch;
    };

}