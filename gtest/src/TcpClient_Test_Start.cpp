#include "TcpClient_Test_Start.h"

using namespace std;
using namespace Test;
using namespace networking;
using namespace std::chrono_literals;

TcpClient_Test_Start::TcpClient_Test_Start()
{
}
TcpClient_Test_Start::~TcpClient_Test_Start() {}

void TcpClient_Test_Start::SetUp()
{
    // Get free TCP port
    port = HelperFunctions::getFreePort();
    ASSERT_EQ(tcpServer.start(port), NETWORKLISTENER_START_OK);
    return;
}

void TcpClient_Test_Start::TearDown()
{
    tcpClient.stop();
    tcpServer.stop();
    return;
}

// ====================================================================================================================
// Desc:       Check if the TCP client starts properly
// Steps:      Start TCP client with correct parameters
// Exp Result: NETWORKCLIENT_START_OK
// ====================================================================================================================
TEST_F(TcpClient_Test_Start, PosTest)
{
    EXPECT_EQ(tcpClient.start("localhost", port), NETWORKCLIENT_START_OK);
    this_thread::sleep_for(1ms);
    EXPECT_EQ(tcpServer.getClientIds().size(), 1);
}

// ====================================================================================================================
// Desc:       Check if client doesn't accept negative port number
// Steps:      Try to start TCP client with -1
// Exp Result: NETWORKCLIENT_ERROR_START_WRONG_PORT
// ====================================================================================================================
TEST_F(TcpClient_Test_Start, NegTest_WrongPort_Negative)
{
    EXPECT_EQ(tcpClient.start("localhost", -1), NETWORKCLIENT_ERROR_START_WRONG_PORT);
    this_thread::sleep_for(1ms);
    EXPECT_EQ(tcpServer.getClientIds().size(), 0);
}

// ====================================================================================================================
// Desc:       Check if client doesn't accept too big port number
// Steps:      Try to start TCP client with 65536
// Exp Result: NETWORKCLIENT_ERROR_START_WRONG_PORT
// ====================================================================================================================
TEST_F(TcpClient_Test_Start, NegTest_WrongPort_TooBig)
{
    EXPECT_EQ(tcpClient.start("localhost", 65536), NETWORKCLIENT_ERROR_START_WRONG_PORT);
    this_thread::sleep_for(1ms);
    EXPECT_EQ(tcpServer.getClientIds().size(), 0);
}

// ====================================================================================================================
// Desc:       Check if client stops properly when server is not running
// Steps:      Try to start TCP client after stopping server
// Exp Result: NETWORKCLIENT_ERROR_START_CONNECT
// ====================================================================================================================
TEST_F(TcpClient_Test_Start, NegTest_ServerNotRunning)
{
    tcpServer.stop();
    EXPECT_EQ(tcpClient.start("localhost", port), NETWORKCLIENT_ERROR_START_CONNECT);
    this_thread::sleep_for(1ms);
    EXPECT_EQ(tcpServer.getClientIds().size(), 0);
}

// ====================================================================================================================
// Desc:       Check if client doesn't start if it is already running
// Steps:      Start TCP client and then try to start it again
// Exp Result: -1
// ====================================================================================================================
TEST_F(TcpClient_Test_Start, NegTest_AlreadyRunning)
{
    ASSERT_EQ(tcpClient.start("localhost", port), NETWORKCLIENT_START_OK);
    EXPECT_EQ(tcpClient.start("localhost", port), -1);
    this_thread::sleep_for(1ms);
    EXPECT_EQ(tcpServer.getClientIds().size(), 1);
}
