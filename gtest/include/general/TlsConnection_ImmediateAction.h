#ifndef GENERAL_TLSCONNECTION_IMMEDIATEACTION_H_
#define GENERAL_TLSCONNECTION_IMMEDIATEACTION_H_

#include <gtest/gtest.h>
#include <chrono>
#include <thread>

#include "TlsServer.h"
#include "TlsClient.h"
#include "HelperFunctions.h"
#include "TestDefines.h"

namespace Test
{
    class General_TlsConnection_ImmediateAction : public testing::Test
    {
    public:
        General_TlsConnection_ImmediateAction();
        virtual ~General_TlsConnection_ImmediateAction();

    protected:
        void SetUp() override;
        void TearDown() override;

        // Port to use
        int port;

        // TLS server and client
        networking::TlsServer tlsServer{'\x00'};
        networking::TlsClient tlsClient{'\x00'};
    };
}

#endif // GENERAL_TLSCONNECTION_IMMEDIATEACTION_H_
