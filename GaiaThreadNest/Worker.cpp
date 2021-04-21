#include "Worker.hpp"


namespace Gaia::ThreadNest
{
    Worker::Worker(Worker &&worker) {
        {
            this->task=worker.task;
            this->Iswork.store(worker.Iswork);
            this->LifeTimestamp=worker.LifeTimestamp;
            this->Frequency=worker.Frequency;
            //todo unique_ptr copy
//            worker.ListPoint.release();
        }
    }


    /**
     * @brief  destruct Worker
     * @version encome a bug while destruct worker, smart ptr ListPoint free memmory double !!!
     */
    Worker::~Worker() {
    }

}