#ifndef HELPERFUNCTIONS_H_
#define HELPERFUNCTIONS_H_

#include <unistd.h>
#include <netinet/in.h>
#include <atomic>
#include <iostream>

class HelperFunctions
{
public:
    /**
     * Find free TCP port
     *
     * @return int next free TCP port
     */
    static int getFreePort();

    /**
     * @brief Set pipe error flag
     */
    static void setPipeError();

    /**
     * @brief Get and reset pipe error flag
     *
     * @return bool false if pipe error flag is not set
     */
    static bool getAndResetPipeError();

private:
    static std::atomic_flag pipeError;
};

#endif // HELPERFUNCTIONS_H_
