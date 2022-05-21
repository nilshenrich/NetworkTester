#ifndef TCP_CLIENT_TEST_SEND_H_
#define TCP_CLIENT_TEST_SEND_H_

#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include <vector>
#include <string>

#include "TcpServerApi.h"
#include "TcpClientApi.h"
#include "HelperFunctions.h"

namespace Test
{
    class TcpClient_Test_Send : public testing::Test
    {
    public:
        TcpClient_Test_Send();
        virtual ~TcpClient_Test_Send();

    protected:
        void SetUp() override;
        void TearDown() override;

        // TCP server and Client
        TestApi::TcpServerApi tcpServer{};
        TestApi::TcpClientApi tcpClient{};

        // Port to use
        int port;
    };
}

#endif // TCP_CLIENT_TEST_SEND_H_
