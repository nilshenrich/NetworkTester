#ifndef TLS_CLIENT_TEST_START_H_
#define TLS_CLIENT_TEST_START_H_

#include <gtest/gtest.h>
#include <chrono>
#include <thread>

#include "TlsServerApi.h"
#include "TlsClientApi.h"
#include "HelperFunctions.h"

namespace Test
{
    class TlsClient_Test_Start : public testing::Test
    {
    public:
        TlsClient_Test_Start();
        virtual ~TlsClient_Test_Start();

    protected:
        void SetUp() override;
        void TearDown() override;

        // TCP server and Client
        TestApi::TlsServerApi tlsServer{};
        TestApi::TlsClientApi tlsClient{};

        // Port to use
        int port;
    };
}

#endif // TLS_CLIENT_TEST_START_H_
