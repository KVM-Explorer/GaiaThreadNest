#pragma once

#include <chrono>

namespace Gaia::ThreadNest
{
    class Timestamp
    {
    public:
        /// Using steady clock as its clock.
        using chrono_clock = std::chrono::steady_clock;

    private:
        /**
         * @brief Time it need to expire.
         * @details
         *  If this timestamp hasn't been renewed after this time duration,
         *  it will expire.
         */
        chrono_clock::duration ExpirationTime;

        /**
         * @brief The time point when this timestamp is renewed.
         * @details
         *  Default value is the time when it is constructed.
         */
        chrono_clock::time_point RenewedTime;

    public:
        /// Constructor with an expiration time of 3 milliseconds.
        Timestamp();
        /// Constructor which will set the expiration time.
        explicit Timestamp(decltype(ExpirationTime) expiration_time);

        /**
         * @brief Check whether this timestamp is still valid or not.
         * @retval true This timestamp is still valid.
         * @retval false This timestamp has been expired and need to be renewed.
         */
        [[nodiscard]] bool IsValid();

        /**
         * @brief Renew this timestamp in order to delay it's expiration time.
         * @details
         *  This function need to be invoked frequently to keep this timestamp valid.
         */
        void Renew();

        /**
         * @brief Get the remaining milliseconds before its expiration.
         * @return After this amount of milliseconds, this timestamp will expire.
         */
        chrono_clock::duration GetRemainingTime();

        /// Check whether this timestamp
        explicit operator bool()
        {
            return IsValid();
        }
    };
}