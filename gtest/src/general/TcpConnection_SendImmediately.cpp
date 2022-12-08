#include "general/TcpConnection_SendImmediately.h"

using namespace std;
using namespace Test;
using namespace networking;

General_TcpConnection_SendImmediately::General_TcpConnection_SendImmediately() {}
General_TcpConnection_SendImmediately::~General_TcpConnection_SendImmediately() {}

void General_TcpConnection_SendImmediately::SetUp()
{
    // Get free TCP port
    port = HelperFunctions::getFreePort();
    ASSERT_NE(port, -1) << "No free port found";

    // Start server and connect client to
    tcpServer.start(port);
    tcpClient.start("localhost", port);

    return;
}

void General_TcpConnection_SendImmediately::TearDown()
{
    // Close client first and server after
    tcpClient.stop();
    tcpServer.stop();

    // Check if no pipe error occurred
    EXPECT_FALSE(HelperFunctions::getAndResetPipeError()) << "Pipe error occurred!";

    return;
}

// ====================================================================================================================
// Desc:       Client sends message immediately after start()-method returns
// Steps:      Start server, start client, send simple message from client to server
// Exp Result: No pipe error occures
// ====================================================================================================================
TEST_F(General_TcpConnection_SendImmediately, ClientToServer)
{
    tcpClient.sendMsg("Test message");
}
