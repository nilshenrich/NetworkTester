#ifndef HELPERFUNCTIONS_H_
#define HELPERFUNCTIONS_H_

#include <unistd.h>
#include <netinet/in.h>

class HelperFunctions
{
public:
    /**
     * Find free TCP port
     *
     * @return int next free TCP port
     */
    static int getFreePort();
};

#endif // HELPERFUNCTIONS_H_
