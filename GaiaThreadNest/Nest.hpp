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
        void AddWorker(Task task);

        void Excute();

    public:

        std::list<Gaia::ThreadNest::Worker> WorkerPool;
        std::list<std::thread> ThreadPool;
    };
}