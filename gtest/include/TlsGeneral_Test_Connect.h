#ifndef TLSGENERAL_TEST_CONNECT_H_
#define TLSGENERAL_TEST_CONNECT_H_

#include <gtest/gtest.h>
#include <chrono>
#include <thread>

#include "TlsServerApi.h"
#include "TlsClientApi.h"
#include "HelperFunctions.h"

namespace Test
{
    class TlsGeneral_Test_Connect : public testing::Test
    {
    public:
        TlsGeneral_Test_Connect();
        virtual ~TlsGeneral_Test_Connect();

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

#endif // TLSGENERAL_TEST_CONNECT_H_
