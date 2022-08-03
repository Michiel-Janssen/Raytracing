#pragma once

#include "tasks/task-scheduler.h"


namespace tasks
{
    namespace schedulers
    {
        TaskScheduler balanced_parallel(unsigned thread_count);
    }
}