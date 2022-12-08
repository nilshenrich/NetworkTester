#include "general/TlsConnection_ImmediateAction.h"

using namespace std;
using namespace Test;
using namespace networking;

General_TlsConnection_ImmediateAction::General_TlsConnection_ImmediateAction() {}
General_TlsConnection_ImmediateAction::~General_TlsConnection_ImmediateAction() {}

void General_TlsConnection_ImmediateAction::SetUp()
{
    // Get free TLS port
    port = HelperFunctions::getFreePort();
    ASSERT_NE(port, -1) << "No free port found";

    // Start server and connect client to
    tlsServer.start(port, KeyPaths::CaCert.c_str(), KeyPaths::ListenerCert.c_str(), KeyPaths::ListenerKey.c_str());
    tlsClient.start("localhost", port, KeyPaths::CaCert.c_str(), KeyPaths::ClientCert.c_str(), KeyPaths::ClientKey.c_str());

    return;
}

void General_TlsConnection_ImmediateAction::TearDown()
{
    // Close client first and server after
    tlsClient.stop();
    tlsServer.stop();

    // Check if no pipe error occurred
    EXPECT_FALSE(HelperFunctions::getAndResetPipeError()) << "Pipe error occurred!";

    return;
}

// ====================================================================================================================
// Desc:       Client stops immediately after start()-method returns
// Steps:      Start server, start client, stop client, stop server
// Exp Result: No pipe error occures
// ====================================================================================================================
TEST_F(General_TlsConnection_ImmediateAction, DoNothing)
{
    // Just do nothing here
    // Server and client are started and stopped in SetUp and TearDown
}

// ====================================================================================================================
// Desc:       Client sends message and stops immediately after start()-method returns
// Steps:      Start server, start client, send simple message from client to server, stop client, stop server
// Exp Result: No pipe error occures
// ====================================================================================================================
TEST_F(General_TlsConnection_ImmediateAction, ClientSends)
{
    tlsClient.sendMsg("Test message");
}
