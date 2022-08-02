#include "tasks/unbalanced-parallel-task-scheduler.h"
#include "easylogging++.h"
#include "unbalanced-parallel-task-scheduler.h"

using namespace tasks;

namespace
{
    class UnbalancedParallelTaskScheduler : public tasks::schedulers::_private_::TaskSchedulerImplementation
    {
    public:
        unsigned thread_count;

        UnbalancedParallelTaskScheduler(unsigned thread_count) : thread_count(thread_count)
        {
        }



        void perform(std::vector<std::shared_ptr<Task>> tasks) const
        {
            std::vector<std::thread> threads;

            /*    Stappenplan
                -------------------
            
               tasks              = vector met alle tasks
               
               sublist.size()    = ceil(tasks.size() / thread_count)

               threads            = vector met alle threads
               threads.size()     = thread_count

               Elke thread krijgt een element van de subtasklist
            */

            auto amountofelementsinlist = ceil(tasks.size() / thread_count);

            for (unsigned i = 0; i < thread_count; i++)
            {
                std::vector<std::shared_ptr<Task>> sublist;

                auto j = 0;
                while (j < amountofelementsinlist && tasks.size() > 0)
                {
                    sublist.push_back(tasks[tasks.size()-1]);
                    tasks.pop_back();
                    j++;
                }


                threads.push_back(
                    std::thread(
                        [sublist]()
                        {
                            for (auto task : sublist)
                            {
                                task->perform();
                            }
                        }
                ));
            }

            // Terminate the thread - after completion

            for (auto& thread : threads)
            {
                thread.join();
            }

        }
    };
}

TaskScheduler tasks::schedulers::unbalanced_parallel(unsigned thread_count)
{
    LOG(INFO) << "Creating unbalanced_parallel scheduler";

    return TaskScheduler(std::make_shared<UnbalancedParallelTaskScheduler>(thread_count));
}
