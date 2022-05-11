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

// ====================================================================================================================
// Desc:       Check if client doesn't accept negative port number
// Steps:      Try to start TLS client with -1
// Exp Result: NETWORKCLIENT_ERROR_START_WRONG_PORT
// ====================================================================================================================
TEST_F(TlsClient_Test_Start, NegTest_WrongPort_Negative)
{
    EXPECT_EQ(tlsClient.start("localhost", -1), NETWORKCLIENT_ERROR_START_WRONG_PORT);
    this_thread::sleep_for(5ms);
    EXPECT_EQ(tlsServer.getClientIds().size(), 0);
}

// ====================================================================================================================
// Desc:       Check if client doesn't accept too big port number
// Steps:      Try to start TLS client with 65536
// Exp Result: NETWORKCLIENT_ERROR_START_WRONG_PORT
// ====================================================================================================================
TEST_F(TlsClient_Test_Start, NegTest_WrongPort_TooBig)
{
    EXPECT_EQ(tlsClient.start("localhost", 65536), NETWORKCLIENT_ERROR_START_WRONG_PORT);
    this_thread::sleep_for(5ms);
    EXPECT_EQ(tlsServer.getClientIds().size(), 0);
}

// ====================================================================================================================
// Desc:       Check if client stops properly when server is not running
// Steps:      Try to start TLS client after stopping server
// Exp Result: NETWORKCLIENT_ERROR_START_CONNECT
// ====================================================================================================================
TEST_F(TlsClient_Test_Start, NegTest_ServerNotRunning)
{
    tlsServer.stop();
    EXPECT_EQ(tlsClient.start("localhost", port), NETWORKCLIENT_ERROR_START_CONNECT);
    this_thread::sleep_for(5ms);
    EXPECT_EQ(tlsServer.getClientIds().size(), 0);
}

// ====================================================================================================================
// Desc:       Check if client doesn't start if it is already running
// Steps:      Try to start TLS client and then try to start it again
// Exp Result: -1
// ====================================================================================================================
TEST_F(TlsClient_Test_Start, NegTest_AlreadyRunning)
{
    EXPECT_EQ(tlsClient.start("localhost", port), NETWORKCLIENT_START_OK);
    EXPECT_EQ(tlsClient.start("localhost", port), -1);
    this_thread::sleep_for(5ms);
    EXPECT_EQ(tlsServer.getClientIds().size(), 1);
}
