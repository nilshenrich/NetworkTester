#ifndef TCP_SERVER_TEST_MANYCLIENTS_H_
#define TCP_SERVER_TEST_MANYCLIENTS_H_

#include <gtest/gtest.h>
#include <thread>
#include <map>
#include <memory>
#include <string>

#include "TcpServerApi.h"
#include "TcpClientApi.h"
#include "HelperFunctions.h"

namespace Test
{
    class TcpServer_Test_ManyClients : public testing::Test
    {
    public:
        TcpServer_Test_ManyClients();
        ~TcpServer_Test_ManyClients();

    protected:
        void SetUp() override;
        void TearDown() override;

        // TCP server and collection of clients
        TestApi::TcpServerApi tcpServer;
        std::map<int, std::unique_ptr<TestApi::TcpClientApi>> tcpClients;
        const int numberOfClients{100};

        // Port to use
        int port;
    };
}

#endif // TCP_SERVER_TEST_MANYCLIENTS_H_
