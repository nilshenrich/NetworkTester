#ifndef TLS_SERVER_TEST_START_H_
#define TLS_SERVER_TEST_START_H_

#include <gtest/gtest.h>

#include "TlsServerApi.h"
#include "HelperFunctions.h"

namespace Test
{
    class TlsServer_Test_Start : public testing::Test
    {
    public:
        TlsServer_Test_Start();
        virtual ~TlsServer_Test_Start();

    protected:
        void SetUp() override;
        void TearDown() override;

        // TLS Server
        TestApi::TlsServerApi tlsServer{};

        // Port to use
        int port;
    };
} // namespace Test

#endif // TLS_SERVER_TEST_START_H_
