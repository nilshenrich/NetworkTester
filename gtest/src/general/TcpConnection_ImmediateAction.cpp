#include "general/TcpConnection_ImmediateAction.h"

using namespace std;
using namespace Test;
using namespace networking;

General_TcpConnection_ImmediateAction::General_TcpConnection_ImmediateAction() {}
General_TcpConnection_ImmediateAction::~General_TcpConnection_ImmediateAction() {}

void General_TcpConnection_ImmediateAction::SetUp()
{
    // Get free TCP port
    port = HelperFunctions::getFreePort();
    ASSERT_NE(port, -1) << "No free port found";

    // Start server and connect client to
    tcpServer.start(port);
    tcpClient.start("localhost", port);

    return;
}

void General_TcpConnection_ImmediateAction::TearDown()
{
    // Close client first and server after
    tcpClient.stop();
    tcpServer.stop();

    // Check if no pipe error occurred
    EXPECT_FALSE(HelperFunctions::getAndResetPipeError()) << "Pipe error occurred!";

    return;
}

// ====================================================================================================================
// Desc:       Client stops immediately after start()-method returns
// Steps:      Start server, start client, stop client, stop server
// Exp Result: No pipe error occures
// ====================================================================================================================
TEST_F(General_TcpConnection_ImmediateAction, DoNothing)
{
    // Just do nothing here
    // Server and client are started and stopped in SetUp and TearDown
}

// ====================================================================================================================
// Desc:       Client sends message and stops immediately after start()-method returns
// Steps:      Start server, start client, send simple message from client to server, stop client, stop server
// Exp Result: No pipe error occures
// ====================================================================================================================
TEST_F(General_TcpConnection_ImmediateAction, ClientSends)
{
    tcpClient.sendMsg("Test message");
}
