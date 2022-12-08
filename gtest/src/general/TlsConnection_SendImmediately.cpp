#include "general/TlsConnection_SendImmediately.h"

using namespace std;
using namespace Test;
using namespace networking;

General_TlsConnection_SendImmediately::General_TlsConnection_SendImmediately() {}
General_TlsConnection_SendImmediately::~General_TlsConnection_SendImmediately() {}

void General_TlsConnection_SendImmediately::SetUp()
{
    // Get free TLS port
    port = HelperFunctions::getFreePort();
    ASSERT_NE(port, -1) << "No free port found";

    // Start server and connect client to
    tlsServer.start(port, KeyPaths::CaCert.c_str(), KeyPaths::ListenerCert.c_str(), KeyPaths::ListenerKey.c_str());
    tlsClient.start("localhost", port, KeyPaths::CaCert.c_str(), KeyPaths::ClientCert.c_str(), KeyPaths::ClientKey.c_str());

    return;
}

void General_TlsConnection_SendImmediately::TearDown()
{
    // Close client first and server after
    tlsClient.stop();
    tlsServer.stop();

    // Check if no pipe error occurred
    EXPECT_FALSE(HelperFunctions::getAndResetPipeError()) << "Pipe error occurred!";

    return;
}

// ====================================================================================================================
// Desc:       Client sends message immediately after start()-method returns
// Steps:      Start server, start client, send simple message from client to server
// Exp Result: No pipe error occures
// ====================================================================================================================
TEST_F(General_TlsConnection_SendImmediately, ClientToServer)
{
    tlsClient.sendMsg("Test message");
}
