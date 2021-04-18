#pragma once

#include "Timestamp.hpp"

namespace Gaia::ThreadNest
{
    class Worker
    {
        friend class Nest;

    private:
        /**
         * @brief The timestamp used to control its life span.
         *        After this timestamp's expiration, the worker thread will automatically terminate.
         * @details
         *  Nest thread uses this timestamp to control worker's life span, and worker thread also uses this
         *  timestamp to know whether nest thread ()
         */
        Timestamp LifeTimestamp;
    };
}