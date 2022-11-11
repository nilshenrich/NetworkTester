#ifndef FRAGMENTATION_TLS_CLIENT_TEST_START_H_
#define FRAGMENTATION_TLS_CLIENT_TEST_START_H_

#include <gtest/gtest.h>
#include <chrono>
#include <thread>

#include "TlsServerApi.h"
#include "TlsClientApi.h"
#include "HelperFunctions.h"

namespace Test
{
    class Fragmentation_TlsClient_Test_Start : public testing::Test
    {
    public:
        Fragmentation_TlsClient_Test_Start();
        virtual ~Fragmentation_TlsClient_Test_Start();

    protected:
        void SetUp() override;
        void TearDown() override;

        // TCP server and Client
        TestApi::TlsServerApi_fragmentation tlsServer{};
        TestApi::TlsClientApi_fragmentation tlsClient{};

        // Port to use
        int port;
    };
}

#endif // FRAGMENTATION_TLS_CLIENT_TEST_START_H_
