#include "tasks/naive-parallel-task-scheduler.h"
#include "easylogging++.h"
#include <vector>

using namespace tasks;


namespace
{
    class NaiveParallelTaskScheduler : public tasks::schedulers::_private_::TaskSchedulerImplementation
    {
    public:
        void perform(std::vector<std::shared_ptr<Task>> tasks) const
        {
            std::vector<std::thread> threads;

            for (auto task : tasks)
            {
                threads.push_back(std::thread([task]()
                    {
                        task->perform();
                    }));
            }

            for (auto& thread : threads)
            {
                thread.join();
            }
        }
    };
}

TaskScheduler tasks::schedulers::naive_parallel()
{
    LOG(INFO) << "Creating naive parallel scheduler";

    return TaskScheduler(std::make_shared<NaiveParallelTaskScheduler>());
}
