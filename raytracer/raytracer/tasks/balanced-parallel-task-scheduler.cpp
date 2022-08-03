#include "tasks/unbalanced-parallel-task-scheduler.h"
#include "easylogging++.h"
#include "balanced-parallel-task-scheduler.h"

using namespace tasks;

namespace
{
    class BalancedParallelTaskScheduler : public tasks::schedulers::_private_::TaskSchedulerImplementation
    {
    public:
        unsigned thread_count;

        BalancedParallelTaskScheduler(unsigned thread_count) : thread_count(thread_count)
        {
        }



        void perform(std::vector<std::shared_ptr<Task>> tasks) const
        {
            std::vector<std::thread> threads;
            std::atomic<int> task_number = { 0 };

            auto threadfunction = [tasks, &task_number]
            {
                while (task_number < tasks.size())
                {
                    auto task = task_number++;
                    tasks[task]->perform();
                }
            };

            while (threads.size() < thread_count)
            {
                threads.push_back(std::thread(threadfunction));
            }



            // Terminate the thread - after completion

            for (auto& thread : threads)
            {
                thread.join();
            }

        }

    };
}

TaskScheduler tasks::schedulers::balanced_parallel(unsigned thread_count)
{
    LOG(INFO) << "Creating balanced_parallel scheduler";

    return TaskScheduler(std::make_shared<BalancedParallelTaskScheduler>(thread_count));
}
