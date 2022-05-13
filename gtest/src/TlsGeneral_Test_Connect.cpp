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

// ====================================================================================================================
// Desc:       Check if the TLS server rejects connections with self signed certificates
// Steps:      Try to connect to server a with self signed certificate
// Exp Result: NETWORKLISTENER_START_OK, NETWORKCLIENT_ERROR_START_CONNECT_INIT
// ====================================================================================================================
TEST_F(TlsGeneral_Test_Connect, NegTest_ClientWithSelfSignedCert)
{
    EXPECT_EQ(tlsServer.start(port, KeyPaths::CaCert, KeyPaths::ListenerCert, KeyPaths::ListenerKey), NETWORKLISTENER_START_OK);
    EXPECT_EQ(tlsClient.start("localhost", port, KeyPaths::CaCert, SelfSignedKeyPaths::ClientCert, SelfSignedKeyPaths::ClientKey), NETWORKCLIENT_ERROR_START_CONNECT_INIT);
    this_thread::sleep_for(5ms);
    EXPECT_EQ(tlsServer.getClientIds().size(), 0);
}

// ====================================================================================================================
// Desc:       Check if the TLS server rejects connections with certificates signed by unknown CA
// Steps:      Try to connect to server a with certificates signed by unknown CA
// Exp Result: NETWORKLISTENER_START_OK, NETWORKCLIENT_ERROR_START_CONNECT_INIT
// ====================================================================================================================
TEST_F(TlsGeneral_Test_Connect, NegTest_ClientWithUnknownCa)
{
    EXPECT_EQ(tlsServer.start(port, KeyPaths::CaCert, KeyPaths::ListenerCert, KeyPaths::ListenerKey), NETWORKLISTENER_START_OK);
    EXPECT_EQ(tlsClient.start("localhost", port, KeyPaths::CaCert, SecondKeyPaths::ClientCert, SecondKeyPaths::ClientKey), NETWORKCLIENT_ERROR_START_CONNECT_INIT);
    this_thread::sleep_for(5ms);
    EXPECT_EQ(tlsServer.getClientIds().size(), 0);
}

// ====================================================================================================================
// Desc:       Check if the TLS server rejects connections with certificates with a certificate chain depth of 2
// Steps:      Try to connect to server a with certificates with a certificate chain depth of 2
// Exp Result: NETWORKLISTENER_START_OK, NETWORKCLIENT_ERROR_START_CONNECT_INIT
// ====================================================================================================================
TEST_F(TlsGeneral_Test_Connect, NegTest_ClientWithCertChainDepth2)
{
    EXPECT_EQ(tlsServer.start(port, KeyPaths::CaCert, KeyPaths::ListenerCert, KeyPaths::ListenerKey), NETWORKLISTENER_START_OK);
    EXPECT_EQ(tlsClient.start("localhost", port, KeyPaths::CaCert, CertChainDepth2KeyPaths::ClientCert, CertChainDepth2KeyPaths::ClientKey), NETWORKCLIENT_ERROR_START_CONNECT_INIT);
    this_thread::sleep_for(5ms);
    EXPECT_EQ(tlsServer.getClientIds().size(), 0);
}
