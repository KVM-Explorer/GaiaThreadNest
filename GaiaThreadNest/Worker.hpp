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
//        friend class Nest;

    public:
        explicit Worker() {}

        Worker(const Worker& worker) {
            this->task=worker.task;
            this->Iswork.store(worker.Iswork);
            this->LifeTimestamp=worker.LifeTimestamp;
            this->Frequency=worker.Frequency;
            //todo unique_ptr copy
//            this->ListPoint=std::move(worker.ListPoint);

        }

        ~Worker(){}



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
        int         Frequency;
        std::unique_ptr<std::thread> ListPoint;
        std::atomic<bool> Iswork;
        Task task;
    };
}