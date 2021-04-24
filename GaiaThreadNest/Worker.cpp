#include "Worker.hpp"

namespace Gaia::ThreadNest
{
    void Worker::Execute()
    {
        IsStart.set_value(true);
    }

    void Worker::Stop()
    {
        auto worker_state = IsStart.get_future();
        // after using std::future get() method, the shared state between Promise and future will be released
        if(worker_state.valid()){
            Execute();
        }
        IsAlive= false;
        if(Thread->joinable())
        {
            Thread->join();
        }
    }
}