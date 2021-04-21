#include "Nest.hpp"
#include <unistd.h>
#include <chrono>

void Gaia::ThreadNest::Nest::AddWorker(Task task, int frequency) {

    Worker worker;
    worker.Iswork= true;
    worker.task=task;
    worker.SetFrequency(int(1/double (frequency)*1000));
    worker.LifeTimestamp=Timestamp(std::chrono::milliseconds (int(1/double (frequency)*1000)));
    WorkerPool.push_back(std::move(worker));
    std::list<Worker>::iterator it;
    it=WorkerPool.end();
    it--;

    /// construct lamda function to add function to ThreadPool
    (*it).ListPoint=std::make_unique<std::thread>(
            std::thread(
                    [this,it]()  ->void {
                        std::future<bool> get_ready_state=(*it).IsStart.get_future();
                        get_ready_state.get();
                        while(true){
                            if((*it).Iswork== false) return;
                            (*it).LifeTimestamp.Renew();
                            (*it).task();
                            std::chrono::duration<double,std::milli>
                                    rest_time=(*it).LifeTimestamp.GetRemainingTime();
                            if(rest_time.count() > 0){
                                usleep(1000 * rest_time.count());
                            }
                        }
                    })
            );


}

void Gaia::ThreadNest::Nest::Excute() {
    std::list<Worker>::iterator it;
    for(it=WorkerPool.begin();it!=WorkerPool.end();it++)
    {
        (*it).IsStart.set_value(true);
    }
}

void Gaia::ThreadNest::Nest::Destory()
{
    std::list<Worker>::iterator it;
    for(it=WorkerPool.begin();it!=WorkerPool.end();it++){
        (*it).Iswork= false;
        if((*it).ListPoint->joinable()){
            (*it).ListPoint->join();
            std::cout<<(*it).ListPoint->get_id()<<std::endl;

//            (*it).ListPoint.reset(nullptr);
        }

    }
}

void Gaia::ThreadNest::Nest::AddWorkerOnce(Gaia::ThreadNest::Nest::Task task) {
    Worker worker;
    worker.Iswork= true;
    worker.task=task;
    WorkerPool.push_back(std::move(worker));
    std::list<Worker>::iterator it;
    it=WorkerPool.end();
    it--;

    /// construct lamda function to add function to ThreadPool
    (*it).ListPoint=std::make_unique<std::thread>(std::thread(
            [this,it]()  ->void {
                (*it).IsStart.get_future();

                if((*it).Iswork== false) return;
                (*it).task();

            })
    );


}
