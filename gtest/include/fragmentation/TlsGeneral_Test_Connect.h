#ifndef FRAGMENTATION_TLS_GENERAL_TEST_CONNECT_H_
#define FRAGMENTATION_TLS_GENERAL_TEST_CONNECT_H_

#include <gtest/gtest.h>
#include <chrono>
#include <thread>

#include "TlsServerApi.h"
#include "TlsClientApi.h"
#include "HelperFunctions.h"

namespace Test
{
    class Fragmentation_TlsGeneral_Test_Connect : public testing::Test
    {
    public:
        Fragmentation_TlsGeneral_Test_Connect();
        virtual ~Fragmentation_TlsGeneral_Test_Connect();

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

#endif // FRAGMENTATION_TLS_GENERAL_TEST_CONNECT_H_
