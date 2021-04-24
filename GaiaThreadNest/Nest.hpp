#pragma once

#include "Worker.hpp"
#include <list>
#include <iterator>
namespace Gaia::ThreadNest
{
    using iterator=std::list<Worker>::iterator;
    class Nest
    {
    public:
        /// WorkGroup is a container to Store Worker
        std::list<Worker> WorkGroup;
    public:
        /**
         * @brief User commit a void() function as a task
         * @param work using Task = std::function<void()> provide an executable function
         *        we named it work
         * @param round means this worker consume maximum time in a round with the millisecond unit
         * @return return a std::list<Worker> iterator to specifically control the single Worker
         * @details Nest use the task to create a Worker which control thread work,
         *          this thread will be trapped in endless loop and become a unit sever,
         *          it will work once in a round if it has rest time, it will sleep for a while
         *          else if it has no time, it will execute the next round immediately
         *          work must be a static method in class or global function
         */
        using Task = std::function<void()> ;
        iterator CommitTask(Task work,int round);

        /**
         * @brief User commit a void() function as a task, which only work once
         * @param work using Task = std::function<void()> provide an executable function
         *        we named it work
         * @details work must be a static method in class or global function
         */
        void CommitTaskOnce(Task work);

        /**
         * @brief Nest use this method to start up all endless loop Worker
         */
        void StartAllTask();

        /**
         * @brief Nest delete specific Worker by use ID
         * @param worker_iterator
         * @details Firstly, stop this worker and then destruct thread, at the end
         *          destroy Worker and delete from WorkerGroups <list>
         */
        void DeleteTask(iterator worker_iterator);

        /**
         * @brief Nest delete all Worker and release sources
         */
        void DeleteAllTask();


    };
}