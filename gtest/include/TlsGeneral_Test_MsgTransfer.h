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
    class TlsGeneral_Test_Messages : public testing::Test
    {
    public:
        TlsGeneral_Test_Messages();
        virtual ~TlsGeneral_Test_Messages();

    protected:
        void SetUp() override;
        void TearDown() override;

        // TLS server and Client
        TestApi::TlsServerApi tlsServer{};
        TestApi::TlsClientApi tlsClient{};

        // Port to use
        int port;

        // Client ID
        int clientId;
    };
}

#endif // TLS_GENERAL_TEST_MESSAGES_H_
