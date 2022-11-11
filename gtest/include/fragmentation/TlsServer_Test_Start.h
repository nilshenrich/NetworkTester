#ifndef FRAGMENTATION_TLS_SERVER_TEST_START_H_
#define FRAGMENTATION_TLS_SERVER_TEST_START_H_

#include <gtest/gtest.h>

#include "TlsServerApi.h"
#include "TlsClientApi.h"
#include "HelperFunctions.h"

namespace Test
{
    class Fragmentation_TlsServer_Test_Start : public testing::Test
    {
    public:
        Fragmentation_TlsServer_Test_Start();
        virtual ~Fragmentation_TlsServer_Test_Start();

    protected:
        void SetUp() override;
        void TearDown() override;

        // TLS Server
        TestApi::TlsServerApi_fragmentation tlsServer{};

        // Port to use
        int port;
    };
} // namespace Test

#endif // FRAGMENTATION_TLS_SERVER_TEST_START_H_
