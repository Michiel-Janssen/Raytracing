#pragma once

#include "tasks/task-scheduler.h"


namespace tasks
{
    namespace schedulers
    {
        TaskScheduler unbalanced_parallel(unsigned thread_count);
    }
}