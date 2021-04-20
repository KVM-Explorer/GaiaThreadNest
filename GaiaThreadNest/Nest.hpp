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
         * @brief Add  function into list but not construct thread and set frequency
         * @param task void() function point
         * @param frequency frequency in 1 second
         */

        void AddWorker(Task task, int frequency);

        void Excute();

        void Destory();

    public:

        std::list<Gaia::ThreadNest::Worker> WorkerPool;
        std::list<std::thread> ThreadPool;
    };
}