#include "TcpClient_Test_Send.h"

using namespace std;
using namespace Test;
using namespace networking;

TcpClient_Test_Send::TcpClient_Test_Send() {}
TcpClient_Test_Send::~TcpClient_Test_Send() {}

void TcpClient_Test_Send::SetUp()
{
    // Get free TCP port
    port = HelperFunctions::getFreePort();

    // Start TCP server and connect client
    ASSERT_EQ(tcpServer.start(port), NETWORKLISTENER_START_OK);
    ASSERT_EQ(tcpClient.start("localhost", port), NETWORKCLIENT_START_OK);
    this_thread::sleep_for(TestConstants::WAITFOR_CONNECT_TCP);

    return;
}

void TcpClient_Test_Send::TearDown()
{
    // Stop TCP server and client
    tcpClient.stop();
    tcpServer.stop();

    // Check if no pipe error occurred
    EXPECT_FALSE(HelperFunctions::getAndResetPipeError()) << "Pipe error occurred!";

    return;
}

// ====================================================================================================================
// Desc:       Send message to server that has stopped running immediately before
// Steps:      Try to send message to server that has stopped running immediately before
// Exp Result: Message is not sent
// ====================================================================================================================
TEST_F(TcpClient_Test_Send, NegTest_ServerNotRunning)
{
    // Stop TCP server
    tcpServer.stop();

    // Send message to server that has stopped running immediately before
    EXPECT_FALSE(tcpClient.sendMsg("Test message"));

    // Check if no message was received by server
    this_thread::sleep_for(TestConstants::WAITFOR_MSG_TCP);
    EXPECT_EQ(tcpServer.getBufferedMsg().size(), 0);

    return;
}

// ====================================================================================================================
// Desc:       Send message to server while client is not running
// Steps:      Try to send message to server while client is not running
// Exp Result: Message is not sent
// ====================================================================================================================
TEST_F(TcpClient_Test_Send, NegTest_ClientNotRunning)
{
    // Stop TCP client
    tcpClient.stop();

    // Send message to server while client is not running
    EXPECT_FALSE(tcpClient.sendMsg("Test message"));

    // Check if no message was received by server
    this_thread::sleep_for(TestConstants::WAITFOR_MSG_TCP);
    EXPECT_EQ(tcpServer.getBufferedMsg().size(), 0);

    return;
}
