#ifndef TLS_CLIENT_TEST_SEND_H_
#define TLS_CLIENT_TEST_SEND_H_

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
    class TlsClient_Test_Send : public testing::Test
    {
    public:
        TlsClient_Test_Send();
        virtual ~TlsClient_Test_Send();

    protected:
        void SetUp() override;
        void TearDown() override;

        // TLS server and Client
        TestApi::TlsServerApi tlsServer{};
        TestApi::TlsClientApi tlsClient{};

        // Port to use
        int port;
    };
}

#endif // TLS_CLIENT_TEST_SEND_H_
