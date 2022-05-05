#include "TlsClient_Test_Start.h"

using namespace std;
using namespace Test;
using namespace networking;
using namespace std::chrono_literals;

TlsClient_Test_Start::TlsClient_Test_Start() {}
TlsClient_Test_Start::~TlsClient_Test_Start() {}

void TlsClient_Test_Start::SetUp()
{
    // Get free TLS port
    port = HelperFunctions::getFreePort();
    ASSERT_EQ(tlsServer.start(port), NETWORKLISTENER_START_OK);
    return;
}

void TlsClient_Test_Start::TearDown()
{
    tlsClient.stop();
    tlsServer.stop();
    return;
}

// ====================================================================================================================
// Desc:       Check if the TLS client starts properly
// Steps:      Start TLS client with correct parameters
// Exp Result: NETWORKCLIENT_START_OK
// ====================================================================================================================
TEST_F(TlsClient_Test_Start, PosTest)
{
    EXPECT_EQ(tlsClient.start("localhost", port), NETWORKCLIENT_START_OK);
    this_thread::sleep_for(5ms);
    EXPECT_EQ(tlsServer.getClientIds().size(), 1);
}
