#ifndef FORWARDING_TCP_CONNECTION_TEST_MSGTRANSFER_H_
#define FORWARDING_TCP_CONNECTION_TEST_MSGTRANSFER_H_

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
    class Forwarding_TcpConnection_Test_MsgTransfer : public testing::Test
    {
    public:
        Forwarding_TcpConnection_Test_MsgTransfer();
        virtual ~Forwarding_TcpConnection_Test_MsgTransfer();

    protected:
        void SetUp() override;
        void TearDown() override;

        // TCP server and Client
        TestApi::TcpServerApi_forwarding tcpServer_selfLong_frgnLong{};
        TestApi::TcpClientApi_forwarding tcpClient_selfLong_frgnLong{};
        TestApi::TcpServerApi_forwarding tcpServer_selfLong_frgnShort{};
        TestApi::TcpClientApi_forwarding tcpClient_selfLong_frgnShort{};
        TestApi::TcpServerApi_forwarding_ShortMsg tcpServer_selfShort_frgnLong{};
        TestApi::TcpClientApi_forwarding_ShortMsg tcpClient_selfShort_frgnLong{};
        TestApi::TcpServerApi_forwarding_ShortMsg tcpServer_selfShort_frgnShort{};
        TestApi::TcpClientApi_forwarding_ShortMsg tcpClient_selfShort_frgnShort{};

        // Port to use
        int port_serverLong_clientLong;
        int port_serverLong_clientShort;
        int port_serverShort_clientLong;
        int port_serverShort_clientShort;

        // Client ID
        int clientId_serverLong_clientLong;
        int clientId_serverLong_clientShort;
        int clientId_serverShort_clientLong;
        int clientId_serverShort_clientShort;
    };
}

#endif // FORWARDING_TCP_CONNECTION_TEST_MSGTRANSFER_H_
