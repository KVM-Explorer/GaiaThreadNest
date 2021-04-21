#include "Worker.hpp"


namespace Gaia::ThreadNest
{
    Worker::Worker(const Worker &worker) {
        {
            this->task=worker.task;
            this->Iswork.store(worker.Iswork);
            this->LifeTimestamp=worker.LifeTimestamp;
            this->Frequency=worker.Frequency;
            //todo unique_ptr copy
//            this->ListPoint;
        }
    }
}