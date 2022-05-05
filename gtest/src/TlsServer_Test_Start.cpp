#include "TlsServer_Test_Start.h"

using namespace std;
using namespace Test;
using namespace networking;

TlsServer_Test_Start::TlsServer_Test_Start() {}
TlsServer_Test_Start::~TlsServer_Test_Start() {}

void TlsServer_Test_Start::SetUp()
{
    // Get free TLS port
    port = HelperFunctions::getFreePort();
    return;
}

void TlsServer_Test_Start::TearDown()
{
    tlsServer.stop();
    return;
}

// ====================================================================================================================
// Desc:       Check if the TLS server starts properly
// Steps:      Start TLS server with correct parameters
// Exp Result: NETWORKLISTENER_START_OK
// ====================================================================================================================
TEST_F(TlsServer_Test_Start, PosTest)
{
    EXPECT_EQ(tlsServer.start(port), NETWORKLISTENER_START_OK);
}

// ====================================================================================================================
// Desc:       Check if server doesn't accept negative port number
// Steps:      Try to start TLS server with -1
// Exp Result: NETWORKLISTENER_ERROR_START_WRONG_PORT
// ====================================================================================================================
TEST_F(TlsServer_Test_Start, NegTest_WrongPort_Negative)
{
    EXPECT_EQ(tlsServer.start(-1), NETWORKLISTENER_ERROR_START_WRONG_PORT);
}

// ====================================================================================================================
// Desc:       Check if server doesn't accept too big port number
// Steps:      Try to start TLS server with 65536
// Exp Result: NETWORKLISTENER_ERROR_START_WRONG_PORT
// ====================================================================================================================
TEST_F(TlsServer_Test_Start, NegTest_WrongPort_TooBig)
{
    EXPECT_EQ(tlsServer.start(65536), NETWORKLISTENER_ERROR_START_WRONG_PORT);
}

// ====================================================================================================================
// Desc:       Check if server doesn't start if it is already running
// Steps:      Start TLS server and then try to start it again
// Exp Result: -1
// ====================================================================================================================
TEST_F(TlsServer_Test_Start, NegTest_AlreadyRunning)
{
    EXPECT_EQ(tlsServer.start(port), NETWORKLISTENER_START_OK);
    EXPECT_EQ(tlsServer.start(port), -1);
}

// ====================================================================================================================
// Desc:       Check if server doesn't start if port is already in use
// Steps:      Start TLS server and try starting another instance with same port
// Exp Result: NETWORKLISTENER_ERROR_START_BIND_PORT
// ====================================================================================================================
TEST_F(TlsServer_Test_Start, NegTest_PortInUse)
{
    ASSERT_EQ(tlsServer.start(port), NETWORKLISTENER_START_OK);
    TestApi::TlsServerApi tlsServer2{};
    EXPECT_EQ(tlsServer2.start(port), NETWORKLISTENER_ERROR_START_BIND_PORT);
}
