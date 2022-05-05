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
    const std::string CaDir{"keys/ca"};
    const std::string CaCert{caDir + "/ca.crt"};
    const std::string CaKey{caDir + "/ca.key"};
    const std::string ServerDir{"keys/server"};
    const std::string ServerCert{ServerDir + "/server.crt"};
    const std::string ServerKey{ServerDir + "/server.key"};
    const std::string ClientDir{"keys/client"};
    const std::string ClientCert{ClientDir + "/client.crt"};
    const std::string ClientKey{ClientDir + "/client.key"};
} // namespace KeyPaths

#endif // TEST_DEFINES_H_
