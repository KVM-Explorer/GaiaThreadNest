#pragma once

#include "Timestamp.hpp"
#include <functional>
#include <atomic>
#include <thread>
#include <list>
#include <memory>
#include <iostream>
#include <chrono>
#include <future>

namespace Gaia::ThreadNest
{
    class Worker
    {

    public:
        explicit Worker() {}
//        Worker(Worker&& target) noexcept;
        Worker( Worker&& worker) ;

        ~Worker();



        void SetFrequency(int frequency)
        {
            Frequency=frequency;
        }

        /**
         * @brief release thread and delete from the list
         */
         void DestoryWorker();

    public:
        using Task= std::function<void()>;
        /**
         * @brief The timestamp used to control its life span.
         *        After this timestamp's expiration, the worker thread will automatically terminate.
         * @details
         *  Nest thread uses this timestamp to control worker's life span, and worker thread also uses this
         *  timestamp to know whether nest thread ()
         */
        Timestamp   LifeTimestamp;
        int         Frequency;                  //once executable cycle  unit is ms
        std::unique_ptr<std::thread> ListPoint; //Point to the thread
        std::atomic<bool> Iswork;           //control the thread whether is alive
        std::promise<bool> IsStart;         //Control the thread whether to execute
        Task task;                          //store the void() function
    };
}