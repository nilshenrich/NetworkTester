#ifndef TCP_GENERAL_TEST_MESSAGES_H_
#define TCP_GENERAL_TEST_MESSAGES_H_

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
    class TcpGeneral_Test_Messages : public testing::Test
    {
    public:
        TcpGeneral_Test_Messages();
        virtual ~TcpGeneral_Test_Messages();

    protected:
        void SetUp() override;
        void TearDown() override;

        // TCP server and Client
        TestApi::TcpServerApi tcpServer{};
        TestApi::TcpClientApi tcpClient{};

        // Port to use
        int port;

        // Client ID
        int clientId;
    };
}

#endif // TCP_GENERAL_TEST_MESSAGES_H_
