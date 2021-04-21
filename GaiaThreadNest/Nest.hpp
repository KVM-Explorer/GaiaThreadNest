#pragma once

#include "Timestamp.hpp"
#include "Worker.hpp"
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
    class Nest
    {
        friend class Worker;
    public:
        Nest(){};

        ~Nest(){};

        using Task = std::function<void()> ;

        /**
         * @brief Add  function into list but not construct thread and set frequency,
         *        all of functions are endless loop and excute all the time
         * @param task void() function point
         * @param frequency frequency in 1 second
         */

        void AddWorker(Task task, int frequency);

        void AddWorkerOnce(Task task);

        void Excute();

        void Destory();

    public:

        std::list<Gaia::ThreadNest::Worker> WorkerPool;
        std::list<std::thread> ThreadPool;
    };
}