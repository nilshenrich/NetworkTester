#ifndef FORWARDING_TLS_CLIENT_TEST_SEND_H_
#define FORWARDING_TLS_CLIENT_TEST_SEND_H_

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
    class Forwarding_TlsClient_Test_Send : public testing::Test
    {
    public:
        Forwarding_TlsClient_Test_Send();
        virtual ~Forwarding_TlsClient_Test_Send();

    protected:
        void SetUp() override;
        void TearDown() override;

        // TLS server and Client
        TestApi::TlsServerApi_forwarding tlsServer{};
        TestApi::TlsClientApi_forwarding tlsClient{};

        // Port to use
        int port;
    };
}

#endif // FORWARDING_TLS_CLIENT_TEST_SEND_H_
