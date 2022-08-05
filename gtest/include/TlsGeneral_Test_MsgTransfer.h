#ifndef TLS_GENERAL_TEST_MESSAGES_H_
#define TLS_GENERAL_TEST_MESSAGES_H_

#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include <vector>
#include <string>

#include "TlsServerApi.h"
#include "TlsClientApi.h"
#include "HelperFunctions.h"

namespace Test
{
    class TlsGeneral_Test_MsgTransfer : public testing::Test
    {
    public:
        TlsGeneral_Test_MsgTransfer();
        virtual ~TlsGeneral_Test_MsgTransfer();

    protected:
        void SetUp() override;
        void TearDown() override;

        // TLS server and Client
        TestApi::TlsServerApi tlsServer_selfLong_frgnLong{};
        TestApi::TlsClientApi tlsClient_selfLong_frgnLong{};
        TestApi::TlsServerApi tlsServer_selfLong_frgnShort{};
        TestApi::TlsClientApi tlsClient_selfLong_frgnShort{};
        TestApi::TlsServerApi_ShortMsg tlsServer_selfShort_frgnLong{};
        TestApi::TlsClientApi_ShortMsg tlsClient_selfShort_frgnLong{};
        TestApi::TlsServerApi_ShortMsg tlsServer_selfShort_frgnShort{};
        TestApi::TlsClientApi_ShortMsg tlsClient_selfShort_frgnShort{};

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

#endif // TLS_GENERAL_TEST_MESSAGES_H_
