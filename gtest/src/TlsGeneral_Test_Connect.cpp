#include "TlsGeneral_Test_Connect.h"

using namespace std;
using namespace Test;
using namespace networking;
using namespace std::chrono_literals;

TlsGeneral_Test_Connect::TlsGeneral_Test_Connect() {}
TlsGeneral_Test_Connect::~TlsGeneral_Test_Connect() {}

void TlsGeneral_Test_Connect::SetUp()
{
    // Get free TLS port
    port = HelperFunctions::getFreePort();
    return;
}

void TlsGeneral_Test_Connect::TearDown()
{
    // Stop TLS server and client
    tlsClient.stop();
    tlsServer.stop();

    // Check if no pipe error occurred
    EXPECT_FALSE(HelperFunctions::getAndResetPipeError()) << "Pipe error occurred!";

    return;
}

// ====================================================================================================================
// Desc:       Check if the TLS client connects to the server properly with good certificates
// Steps:      Connect to server with good certificates
// Exp Result: NETWORKLISTENER_START_OK, NETWORKCLIENT_START_OK
// ====================================================================================================================
TEST_F(TlsGeneral_Test_Connect, PosTest_MainCerts)
{
    EXPECT_EQ(tlsServer.start(port, KeyPaths::CaCert, KeyPaths::ListenerCert, KeyPaths::ListenerKey), NETWORKLISTENER_START_OK);
    EXPECT_EQ(tlsClient.start("localhost", port, KeyPaths::CaCert, KeyPaths::ClientCert, KeyPaths::ClientKey), NETWORKCLIENT_START_OK);
    this_thread::sleep_for(5ms);
    EXPECT_EQ(tlsServer.getClientIds().size(), 1);
}

// ====================================================================================================================
// Desc:       Check if the TLS client connects to the server properly with second certificates
// Steps:      Connect to server with second certificates
// Exp Result: NETWORKLISTENER_START_OK, NETWORKCLIENT_START_OK
// ====================================================================================================================
TEST_F(TlsGeneral_Test_Connect, PosTest_SecondCerts)
{
    EXPECT_EQ(tlsServer.start(port, SecondKeyPaths::CaCert, SecondKeyPaths::ListenerCert, SecondKeyPaths::ListenerKey), NETWORKLISTENER_START_OK);
    EXPECT_EQ(tlsClient.start("localhost", port, SecondKeyPaths::CaCert, SecondKeyPaths::ClientCert, SecondKeyPaths::ClientKey), NETWORKCLIENT_START_OK);
    this_thread::sleep_for(5ms);
    EXPECT_EQ(tlsServer.getClientIds().size(), 1);
}
