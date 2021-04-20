#include "Nest.hpp"
#include <unistd.h>
#include <chrono>

void Gaia::ThreadNest::Nest::AddWorker(Task task, int frequency) {

    Worker worker;
    worker.Iswork= true;
    worker.task=task;
    worker.SetFrequency(int(1/double (frequency)*1000));
    worker.LifeTimestamp=Timestamp(std::chrono::milliseconds (int(1/double (frequency)*1000)));
    WorkerPool.push_back(worker);
}

void Gaia::ThreadNest::Nest::Excute() {
    std::list<Worker>::iterator it;
    for(it=WorkerPool.begin();it!=WorkerPool.end();it++)
    {
        ThreadPool.push_back(std::thread(

                [this,it]()  ->void {
                    while(true){
                        if((*it).Iswork== false) return;

                        (*it).LifeTimestamp.Renew();
                        (*it).task();

                        std::chrono::duration<double,std::milli> rest_time=(*it).LifeTimestamp.GetRemainingTime();

                        if(rest_time.count() > 0){
                            usleep(1000 * rest_time.count());
                        }
                    }
                })
                );
        (*it).ListPoint = (std::unique_ptr<std::thread>) &ThreadPool.back();
    }
}

void Gaia::ThreadNest::Nest::Destory()
{
    std::list<Worker>::iterator it;
    for(it=WorkerPool.begin();it!=WorkerPool.end();it++){
        if((*it).ListPoint->joinable()){
            (*it).Iswork= false;
            (*it).ListPoint->join();
        }
    }
}
