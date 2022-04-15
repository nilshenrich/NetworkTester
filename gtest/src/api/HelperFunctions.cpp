#include "HelperFunctions.h"

using namespace std;

int HelperFunctions::getFreePort()
{
    for (int port{8081}; port < 65536; port += 1)
    {
        int sock{socket(AF_INET, SOCK_STREAM, 0)};
        if (-1 == sock)
            return -1;

        struct sockaddr_in sin;
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr = INADDR_ANY;
        sin.sin_port = htons(port);

        if (!bind(sock, (struct sockaddr *)&sin, sizeof(sin)))
        {
            close(sock);
            return port;
        }
    }

    // If we get here, no free port was found. Return -1.
    return -1;
}
