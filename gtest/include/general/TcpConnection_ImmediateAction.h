#ifndef GENERAL_TCPCONNECTION_IMMEDIATEACTION_H_
#define GENERAL_TCPCONNECTION_IMMEDIATEACTION_H_

#include <gtest/gtest.h>
#include <chrono>
#include <thread>

#include "TcpServer.h"
#include "TcpClient.h"
#include "HelperFunctions.h"

namespace Test
{
    class General_TcpConnection_ImmediateAction : public testing::Test
    {
    public:
        General_TcpConnection_ImmediateAction();
        virtual ~General_TcpConnection_ImmediateAction();

    protected:
        void SetUp() override;
        void TearDown() override;

        // Port to use
        int port;

        // TCP server and client
        networking::TcpServer tcpServer{'\x00'};
        networking::TcpClient tcpClient{'\x00'};
    };
}

#endif // GENERAL_TCPCONNECTION_IMMEDIATEACTION_H_
