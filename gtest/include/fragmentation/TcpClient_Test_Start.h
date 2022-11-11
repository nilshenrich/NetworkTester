#ifndef FRAGMENTATION_TCP_CLIENT_TEST_START_H_
#define FRAGMENTATION_TCP_CLIENT_TEST_START_H_

#include <gtest/gtest.h>
#include <chrono>
#include <thread>

#include "TcpServerApi.h"
#include "TcpClientApi.h"
#include "HelperFunctions.h"

namespace Test
{
    class Fragmentation_TcpClient_Test_Start : public testing::Test
    {
    public:
        Fragmentation_TcpClient_Test_Start();
        virtual ~Fragmentation_TcpClient_Test_Start();

    protected:
        void SetUp() override;
        void TearDown() override;

        // TCP server and Client
        TestApi::TcpServerApi_fragmentation tcpServer{};
        TestApi::TcpClientApi_fragmentation tcpClient{};

        // Port to use
        int port;
    };
}

#endif // FRAGMENTATION_TCP_CLIENT_TEST_START_H_
