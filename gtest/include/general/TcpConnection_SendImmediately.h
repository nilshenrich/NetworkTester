#ifndef GENERAL_TCPCONNECTION_SENDIMMEDIATELY_H_
#define GENERAL_TCPCONNECTION_SENDIMMEDIATELY_H_

#include <gtest/gtest.h>
#include <chrono>
#include <thread>

#include "TcpServer.h"
#include "TcpClient.h"
#include "HelperFunctions.h"

namespace Test
{
    class General_TcpConnection_SendImmediately : public testing::Test
    {
    public:
        General_TcpConnection_SendImmediately();
        virtual ~General_TcpConnection_SendImmediately();

    protected:
        void SetUp() override;
        void TearDown() override;

        // Port to use
        int port;
    };
}

#endif // GENERAL_TCPCONNECTION_SENDIMMEDIATELY_H_
