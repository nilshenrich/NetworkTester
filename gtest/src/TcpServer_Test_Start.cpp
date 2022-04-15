#include "TcpServer_Test_Start.h"

using namespace std;
using namespace Test;
using namespace networking;

TcpServer_Test_Start::TcpServer_Test_Start() {}
TcpServer_Test_Start::~TcpServer_Test_Start() {}

void TcpServer_Test_Start::SetUp()
{
    // Get free TCP port
    port = HelperFunctions::getFreePort();
    return;
}

void TcpServer_Test_Start::TearDown()
{
    tcpServer.stop();
    return;
}

// ====================================================================================================================
// Desc:       Check if the TCP server starts properly
// Steps:      Start TCP server with correct parameters
// Exp Result: NETWORKLISTENER_START_OK
// ====================================================================================================================
TEST_F(TcpServer_Test_Start, PosTest)
{
    EXPECT_EQ(tcpServer.start(port), NETWORKLISTENER_START_OK);
}

// ====================================================================================================================
// Desc:       Check if server doesn't accept negative port number
// Steps:      Try to start TCP server with -1
// Exp Result: NETWORKLISTENER_ERROR_START_WRONG_PORT
// ====================================================================================================================
TEST_F(TcpServer_Test_Start, NegTest_WrongPort_Negative)
{
    EXPECT_EQ(tcpServer.start(-1), NETWORKLISTENER_ERROR_START_WRONG_PORT);
}

// ====================================================================================================================
// Desc:       Check if server doesn't accept too big port number
// Steps:      Try to start TCP server with 65536
// Exp Result: NETWORKLISTENER_ERROR_START_WRONG_PORT
// ====================================================================================================================
TEST_F(TcpServer_Test_Start, NegTest_WrongPort_TooBig)
{
    EXPECT_EQ(tcpServer.start(65536), NETWORKLISTENER_ERROR_START_WRONG_PORT);
}

// ====================================================================================================================
// Desc:       Check if server doesn't start if it is already running
// Steps:      Start TCP server and then try to start it again
// Exp Result: -1
// ====================================================================================================================
TEST_F(TcpServer_Test_Start, NegTest_AlreadyRunning)
{
    EXPECT_EQ(tcpServer.start(port), NETWORKLISTENER_START_OK);
    EXPECT_EQ(tcpServer.start(port), -1);
}

// ====================================================================================================================
// Desc:       Check if server doesn't start if port is already in use
// Steps:      Start TCP server and try starting another instance with same port
// Exp Result: NETWORKLISTENER_ERROR_START_BIND_PORT
// ====================================================================================================================
TEST_F(TcpServer_Test_Start, NegTest_PortInUse)
{
    ASSERT_EQ(tcpServer.start(port), NETWORKLISTENER_START_OK);
    TestApi::TcpServerApi tcpServer2{};
    EXPECT_EQ(tcpServer2.start(port), NETWORKLISTENER_ERROR_START_BIND_PORT);
}
