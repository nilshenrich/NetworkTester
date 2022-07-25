#ifndef TLS_SERVER_TEST_MANYCLIENTS_H_
#define TLS_SERVER_TEST_MANYCLIENTS_H_

#include <gtest/gtest.h>
#include <chrono> // TODO: Remove when feature/connectionEstablish merged
#include <thread>
#include <map>
#include <memory>
#include <string>

#include "TlsServerApi.h"
#include "TlsClientApi.h"
#include "HelperFunctions.h"

namespace Test
{
    class TlsServer_Test_ManyClients : public testing::Test
    {
    public:
        TlsServer_Test_ManyClients();
        ~TlsServer_Test_ManyClients();

    protected:
        void SetUp() override;
        void TearDown() override;

        // TLS server and collection of clients
        TestApi::TlsServerApi tlsServer;
        std::map<int, std::unique_ptr<TestApi::TlsClientApi>> tlsClients;
        const int numberOfClients{100};

        // Port to use
        int port;
    };
}

#endif // TLS_SERVER_TEST_MANYCLIENTS_H_
