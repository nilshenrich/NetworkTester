#include "TlsClient_Test_Send.h"

using namespace std;
using namespace Test;
using namespace networking;

TlsClient_Test_Send::TlsClient_Test_Send() {}
TlsClient_Test_Send::~TlsClient_Test_Send() {}

void TlsClient_Test_Send::SetUp()
{
    // Get free TLS port
    port = HelperFunctions::getFreePort();

    // Start TLS server and connect client
    ASSERT_EQ(tlsServer.start(port), NETWORKLISTENER_START_OK);
    ASSERT_EQ(tlsClient.start("localhost", port), NETWORKCLIENT_START_OK);
    this_thread::sleep_for(TestConstants::WAITFOR_CONNECT_TLS);

    return;
}

void TlsClient_Test_Send::TearDown()
{
    // Stop TLS server and client
    tlsClient.stop();
    tlsServer.stop();

    // Check if no pipe error occurred
    EXPECT_FALSE(HelperFunctions::getAndResetPipeError()) << "Pipe error occurred!";

    return;
}

// ====================================================================================================================
// Desc:       Send message to server that has stopped running immediately before
// Steps:      Try to send message to server that has stopped running immediately before
// Exp Result: Message is not sent
// ====================================================================================================================
TEST_F(TlsClient_Test_Send, NegTest_ServerNotRunning)
{
    // Stop TLS server
    tlsServer.stop();

    // Send message to server that has stopped running immediately before
    EXPECT_FALSE(tlsClient.sendMsg("Test message"));

    // Check if no message was received by server
    this_thread::sleep_for(TestConstants::WAITFOR_MSG_TLS);
    EXPECT_EQ(tlsServer.getBufferedMsg().size(), 0);

    return;
}

// ====================================================================================================================
// Desc:       Send message to server while client is not running
// Steps:      Try to send message to server while client is not running
// Exp Result: Message is not sent
// ====================================================================================================================
TEST_F(TlsClient_Test_Send, NegTest_ClientNotRunning)
{
    // Stop TLS client
    tlsClient.stop();

    // Send message to server while client is not running
    EXPECT_FALSE(tlsClient.sendMsg("Test message"));

    // Check if no message was received by server
    this_thread::sleep_for(TestConstants::WAITFOR_MSG_TLS);
    EXPECT_EQ(tlsServer.getBufferedMsg().size(), 0);

    return;
}
