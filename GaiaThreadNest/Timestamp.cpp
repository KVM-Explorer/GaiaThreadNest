#include "Timestamp.hpp"

namespace Gaia::ThreadNest
{
    /// Default constructor
    Timestamp::Timestamp() : Timestamp(std::chrono::milliseconds(3))
    {}

    /// Constructor which will set the expiration time.
    Timestamp::Timestamp(decltype(ExpirationTime) expiration_time) :
        ExpirationTime(expiration_time), RenewedTime(chrono_clock::now())
    {}

    /// Check whether this timestamp is still valid or not.
    bool Timestamp::IsValid()
    {
        return (chrono_clock::now() - RenewedTime) < ExpirationTime;
    }

    /// Renew this timestamp in order to delay it's expiration time.
    void Timestamp::Renew()
    {
        RenewedTime = chrono_clock::now();
    }

    /// Get the remaining milliseconds before its expiration.
    Timestamp::chrono_clock::duration Timestamp::GetRemainingTime()
    {
        return ExpirationTime - (chrono_clock::now() - RenewedTime);
    }
}