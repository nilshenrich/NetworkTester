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
    class TcpGeneral_Test_MsgTransfer : public testing::Test
    {
    public:
        TcpGeneral_Test_MsgTransfer();
        virtual ~TcpGeneral_Test_MsgTransfer();

    protected:
        void SetUp() override;
        void TearDown() override;

        // TCP server and Client
        TestApi::TcpServerApi tcpServer_selfLong_frgnLong{};
        TestApi::TcpClientApi tcpClient_selfLong_frgnLong{};

        // Port to use
        int port_serverLong_clientLong;

        // Client ID
        int clientId_serverLong_clientLong;
    };
}

#endif // TCP_GENERAL_TEST_MESSAGES_H_
