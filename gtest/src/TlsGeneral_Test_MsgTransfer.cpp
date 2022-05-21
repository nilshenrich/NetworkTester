#include "TlsGeneral_Test_MsgTransfer.h"

using namespace std;
using namespace Test;
using namespace networking;

TlsGeneral_Test_Messages::TlsGeneral_Test_Messages() {}
TlsGeneral_Test_Messages::~TlsGeneral_Test_Messages() {}

void TlsGeneral_Test_Messages::SetUp()
{
    // Get free TLS port
    port = HelperFunctions::getFreePort();

    // Start TLS server and connect client
    ASSERT_EQ(tlsServer.start(port), NETWORKLISTENER_START_OK);
    ASSERT_EQ(tlsClient.start("localhost", port), NETWORKCLIENT_START_OK);
    this_thread::sleep_for(TestConstants::WAITFOR_CONNECT_TLS);

    // Get client ID
    vector<int> clientIds{tlsServer.getClientIds()};
    ASSERT_EQ(clientIds.size(), 1);
    clientId = clientIds[0];

    return;
}

void TlsGeneral_Test_Messages::TearDown()
{
    // Stop TLS server and client
    tlsClient.stop();
    tlsServer.stop();

    // Check if no pipe error occurred
    EXPECT_FALSE(HelperFunctions::getAndResetPipeError()) << "Pipe error occurred!";

    return;
}

// ====================================================================================================================
// Desc:       Send normal message from client to server
// Steps:      Send normal message from client to server
// Exp Result: Message received by server
// ====================================================================================================================
TEST_F(TlsGeneral_Test_Messages, PosTest_ClientToServer_NormalMsg)
{
    // Send message from client to server
    string msg{"Hello server!"};
    EXPECT_TRUE(tlsClient.sendMsg(msg));
    this_thread::sleep_for(TestConstants::WAITFOR_MSG_TLS);

    // Check if message received by server
    vector<TestApi::MessageFromClient> messagesExpected{TestApi::MessageFromClient{clientId, msg}};
    EXPECT_EQ(tlsServer.getBufferedMsg(), messagesExpected);
}

// ====================================================================================================================
// Desc:       Send normal message from server to client
// Steps:      Send normal message from server to client
// Exp Result: Message received by client
// ====================================================================================================================
TEST_F(TlsGeneral_Test_Messages, PosTest_ServerToClient_NormalMsg)
{
    // Send message from server to client
    string msg{"Hello client!"};
    EXPECT_TRUE(tlsServer.sendMsg(clientId, msg));
    this_thread::sleep_for(TestConstants::WAITFOR_MSG_TLS);

    // Check if message received by client
    vector<string> messagesExpected{msg};
    EXPECT_EQ(tlsClient.getBufferedMsg(), messagesExpected);
}

// ====================================================================================================================
// Desc:       Send long message from client to server
// Steps:      Send long message from client to server (1000000 bytes)
// Exp Result: Message received by server
// ====================================================================================================================
TEST_F(TlsGeneral_Test_Messages, PosTest_ClientToServer_LongMsg)
{
    // Generate message with 1000000 elements of ASCII characters 33 - 126
    string msg;
    for (int i = 0; i < 1000000; i += 1)
        msg += static_cast<char>(i % 94 + 33);

    // Send message from client to server
    EXPECT_TRUE(tlsClient.sendMsg(msg));
    this_thread::sleep_for(TestConstants::WAITFOR_MSG_LONG_TLS);

    // Check if message received by server
    vector<TestApi::MessageFromClient> messagesExpected{TestApi::MessageFromClient{clientId, msg}};
    EXPECT_EQ(tlsServer.getBufferedMsg(), messagesExpected);
}

// ====================================================================================================================
// Desc:       Send long message from server to client
// Steps:      Send long message from server to client (1000000 bytes)
// Exp Result: Message received by client
// ====================================================================================================================
TEST_F(TlsGeneral_Test_Messages, PosTest_ServerToClient_LongMsg)
{
    // Generate message with 1000000 elements of ASCII characters 33 - 126
    string msg;
    for (int i = 0; i < 1000000; i += 1)
        msg += static_cast<char>(i % 94 + 33);

    // Send message from server to client
    EXPECT_TRUE(tlsServer.sendMsg(clientId, msg));
    this_thread::sleep_for(TestConstants::WAITFOR_MSG_LONG_TLS);

    // Check if message received by client
    vector<string> messagesExpected{msg};
    EXPECT_EQ(tlsClient.getBufferedMsg(), messagesExpected);
}
