#ifndef TCP_SERVER_TEST_START_H_
#define TCP_SERVER_TEST_START_H_

#include <gtest/gtest.h>

#include "TcpServerApi.h"
#include "HelperFunctions.h"

namespace Test
{
    class TcpServer_Test_Start : public testing::Test
    {
    public:
        TcpServer_Test_Start();
        virtual ~TcpServer_Test_Start();

    protected:
        void SetUp() override;
        void TearDown() override;

        // TCP Server
        TestApi::TcpServerApi tcpServer{};

        // Port to use
        int port;
    };
} // namespace Test

#endif // TCP_SERVER_TEST_START_H_
