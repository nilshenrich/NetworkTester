#include "TcpGeneral_Test_MsgTransfer.h"

using namespace std;
using namespace Test;
using namespace networking;

TcpGeneral_Test_Messages::TcpGeneral_Test_Messages() {}
TcpGeneral_Test_Messages::~TcpGeneral_Test_Messages() {}

void TcpGeneral_Test_Messages::SetUp()
{
    // Get free TCP port
    port = HelperFunctions::getFreePort();

    // Start TCP server and connect client
    ASSERT_EQ(tcpServer.start(port), NETWORKLISTENER_START_OK);
    ASSERT_EQ(tcpClient.start("localhost", port), NETWORKCLIENT_START_OK);
    this_thread::sleep_for(TestConstants::WAITFORTCP);

    // Get client ID
    vector<int> clientIds{tcpServer.getClientIds()};
    ASSERT_EQ(clientIds.size(), 1);
    clientId = clientIds[0];

    return;
}

void TcpGeneral_Test_Messages::TearDown()
{
    // Stop TCP server and client
    tcpClient.stop();
    tcpServer.stop();

    // Check if no pipe error occurred
    EXPECT_FALSE(HelperFunctions::getAndResetPipeError()) << "Pipe error occurred!";

    return;
}

// ====================================================================================================================
// Desc:       Send normal message from client to server
// Steps:      Send normal message from client to server
// Exp Result: Message received by server
// ====================================================================================================================
TEST_F(TcpGeneral_Test_Messages, PosTest_ClientToServer_NormalMsg)
{
    // Send message from client to server
    string msg{"Hello server!"};
    EXPECT_TRUE(tcpClient.sendMsg(msg));
    this_thread::sleep_for(TestConstants::WAITFORTCP);

    // Check if message received by server
    vector<TestApi::MessageFromClient> messagesExpected{TestApi::MessageFromClient{clientId, msg}};
    EXPECT_EQ(tcpServer.getBufferedMsg(), messagesExpected);
}

// ====================================================================================================================
// Desc:       Send normal message from server to client
// Steps:      Send normal message from server to client
// Exp Result: Message received by client
// ====================================================================================================================
TEST_F(TcpGeneral_Test_Messages, PosTest_ServerToClient_NormalMsg)
{
    // Send message from server to client
    string msg{"Hello client!"};
    EXPECT_TRUE(tcpServer.sendMsg(clientId, msg));
    this_thread::sleep_for(TestConstants::WAITFORTCP);

    // Check if message received by client
    vector<string> messagesExpected{msg};
    EXPECT_EQ(tcpClient.getBufferedMsg(), messagesExpected);
}
