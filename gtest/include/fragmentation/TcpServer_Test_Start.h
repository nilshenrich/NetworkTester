#ifndef FRAGMENTATION_TCP_SERVER_TEST_START_H_
#define FRAGMENTATION_TCP_SERVER_TEST_START_H_

#include <gtest/gtest.h>

#include "TcpServerApi.h"
#include "TcpClientApi.h"
#include "HelperFunctions.h"

namespace Test
{
    class Fragmentation_TcpServer_Test_Start : public testing::Test
    {
    public:
        Fragmentation_TcpServer_Test_Start();
        virtual ~Fragmentation_TcpServer_Test_Start();

    protected:
        void SetUp() override;
        void TearDown() override;

        // TCP Server
        TestApi::TcpServerApi_fragmentation tcpServer{};

        // Port to use
        int port;
    };
} // namespace Test

#endif // FRAGMENTATION_TCP_SERVER_TEST_START_H_
