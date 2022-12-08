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
    return;
}

void General_TlsConnection_SendImmediately::TearDown()
{
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
    TlsServer server{'\x00'};
    TlsClient client{'\x00'};
    server.start(port, KeyPaths::CaCert.c_str(), KeyPaths::ListenerCert.c_str(), KeyPaths::ListenerKey.c_str());
    client.start("localhost", port, KeyPaths::CaCert.c_str(), KeyPaths::ClientCert.c_str(), KeyPaths::ClientKey.c_str());
    client.sendMsg("Test message");
}
