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
    const std::string rootDir{"../../keys"};
    const std::string CaDir{rootDir + "/ca"};
    const std::string CaCert{CaDir + "/ca.crt"};
    const std::string CaKey{CaDir + "/ca.key"};
    const std::string ListenerDir{rootDir + "/listener"};
    const std::string ListenerCert{ListenerDir + "/listener.crt"};
    const std::string ListenerKey{ListenerDir + "/listener.key"};
    const std::string ClientDir{rootDir + "/client"};
    const std::string ClientCert{ClientDir + "/client.crt"};
    const std::string ClientKey{ClientDir + "/client.key"};
} // namespace KeyPaths

namespace FakeKeyPaths
{
    const std::string rootDir{"../../fakeKeys"};
    const std::string CaDir{rootDir + "/ca"};
    const std::string CaCert{CaDir + "/ca.crt"};
    const std::string CaKey{CaDir + "/ca.key"};
    const std::string ListenerDir{rootDir + "/listener"};
    const std::string ListenerCert{ListenerDir + "/listener.crt"};
    const std::string ListenerKey{ListenerDir + "/listener.key"};
    const std::string ClientDir{rootDir + "/client"};
    const std::string ClientCert{ClientDir + "/client.crt"};
    const std::string ClientKey{ClientDir + "/client.key"};
} // namespace KeyPaths

namespace SelfSignedKeyPaths
{
    const std::string rootDir{"../../selfSignedKeys"};
    const std::string CaDir{rootDir + "/ca"};
    const std::string CaCert{CaDir + "/ca.crt"};
    const std::string CaKey{CaDir + "/ca.key"};
    const std::string ListenerDir{rootDir + "/listener"};
    const std::string ListenerCert{ListenerDir + "/listener.crt"};
    const std::string ListenerKey{ListenerDir + "/listener.key"};
    const std::string ClientDir{rootDir + "/client"};
    const std::string ClientCert{ClientDir + "/client.crt"};
    const std::string ClientKey{ClientDir + "/client.key"};
} // namespace KeyPaths

#endif // TEST_DEFINES_H_
