#ifndef TEST_DEFINES_H_
#define TEST_DEFINES_H_

#include <string>

namespace TestApi
{
    // Message from TCP/TLS client (Client ID, Message)
    struct MessageFromClient
    {
        int id;
        std::string msg;
    };
} // namespace TestApi

namespace KeyPaths
{
    const std::string CaCert{};
    const std::string CaKey{};
    const std::string ServerCert{};
    const std::string ServerKey{};
    const std::string ClientCert{};
    const std::string ClientKey{};
} // namespace KeyPaths

#endif // TEST_DEFINES_H_
