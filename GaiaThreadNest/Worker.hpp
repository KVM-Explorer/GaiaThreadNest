#pragma once

#include "Timestamp.hpp"
#include <functional>
#include <atomic>
#include <thread>
#include <memory>
#include <future>

namespace Gaia::ThreadNest
{
    class Worker
    {
        using Task = std::function<void()> ;
    private:
        /**
         * @brief The timestamp used to control its life span.
         *        After this timestamp's expiration, the worker thread will automatically terminate.
         * @details
         *  Nest thread uses this timestamp to control worker's life span, and worker thread also uses this
         *  timestamp to know whether nest thread ()
         */
        Timestamp LifeTimestamp;
        Task Work;                                //work is what this worker should do
        std::unique_ptr<std::thread> Thread;     //thread point
        std::atomic<bool> IsAlive;               //control this thread is alive if false this thread should be killed
        std::promise<bool> IsStart;              //Async control thread start up to work
    public:
        /**
         * @brief stop this worker's work
         * @details Nest can throughout this to control Worker
         *          After use this Worker's work is stopped and relevant sources are released
         */
        void Stop();

        /**
         * @brief Nest use this to start up Worker
         * @details thread has been built, but it don't work immediately because of IsStart
         *          thus it can archive async operate
         */
        void Execute();

    };
}