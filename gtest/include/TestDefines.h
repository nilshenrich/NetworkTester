#include <string>

namespace TestApi
{
    // Message from TCP/TLS client (Client ID, Message)
    struct MessageFromClient
    {
        int id;
        std::string msg;
    };
}
