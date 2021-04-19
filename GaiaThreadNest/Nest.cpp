#include "Nest.hpp"



void Gaia::ThreadNest::Nest::AddWorker(Task task) {
    Worker worker;
    worker.Iswork= true;
    worker.task=task;
    WorkerPool.push_back(worker);
}

void Gaia::ThreadNest::Nest::Excute() {
    std::list<Worker>::iterator it;
    for(it=WorkerPool.begin();it!=WorkerPool.end();it++)
    {
        ThreadPool.push_back(std::thread(

                [this,it]()  ->void {
                    if((*it).Iswork== false) return;
                    (*it).task();
                })
                );
    }
}
