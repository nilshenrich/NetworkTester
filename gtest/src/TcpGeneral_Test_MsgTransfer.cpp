// TODO: Add tests: Send/Receive maxLen/TooLong msg in both directions

#include "TcpGeneral_Test_MsgTransfer.h"

using namespace std;
using namespace Test;
using namespace networking;

TcpGeneral_Test_MsgTransfer::TcpGeneral_Test_MsgTransfer() {}
TcpGeneral_Test_MsgTransfer::~TcpGeneral_Test_MsgTransfer() {}

void TcpGeneral_Test_MsgTransfer::SetUp()
{
    // Get free TCP port
    port = HelperFunctions::getFreePort();

    // Start TCP server and connect client
    ASSERT_EQ(tcpServer.start(port), NETWORKLISTENER_START_OK);
    ASSERT_EQ(tcpClient.start("localhost", port), NETWORKCLIENT_START_OK);

    // Get client ID
    vector<int> clientIds{tcpServer.getClientIds()};
    ASSERT_EQ(clientIds.size(), 1);
    clientId = clientIds[0];

    return;
}

void TcpGeneral_Test_MsgTransfer::TearDown()
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
TEST_F(TcpGeneral_Test_MsgTransfer, PosTest_ClientToServer_NormalMsg)
{
    // Send message from client to server
    string msg{"Hello server!"};
    EXPECT_TRUE(tcpClient.sendMsg(msg));
    this_thread::sleep_for(TestConstants::WAITFOR_MSG_TCP);

    // Check if message received by server
    vector<TestApi::MessageFromClient> messagesExpected{TestApi::MessageFromClient{clientId, msg}};
    EXPECT_EQ(tcpServer.getBufferedMsg(), messagesExpected);
}

// ====================================================================================================================
// Desc:       Send normal message from server to client
// Steps:      Send normal message from server to client
// Exp Result: Message received by client
// ====================================================================================================================
TEST_F(TcpGeneral_Test_MsgTransfer, PosTest_ServerToClient_NormalMsg)
{
    // Send message from server to client
    string msg{"Hello client!"};
    EXPECT_TRUE(tcpServer.sendMsg(clientId, msg));
    this_thread::sleep_for(TestConstants::WAITFOR_MSG_TCP);

    // Check if message received by client
    vector<string> messagesExpected{msg};
    EXPECT_EQ(tcpClient.getBufferedMsg(), messagesExpected);
}

// TODO: Implement test
// ====================================================================================================================
// Desc:       Send message with max length from client to server
// Steps:      Send message with max length from short client to short server
// Exp Result: Message receive by server
// ====================================================================================================================

// TODO: Implement test
// ====================================================================================================================
// Desc:       Send message exceeding max receiving length from client to server
// Steps:      Send message with length max+1 from long client to short server
// Exp Result: Message sent but not received
// ====================================================================================================================

// TODO: Implement test
// ====================================================================================================================
// Desc:       Send message exceeding max sending length from client to server
// Steps:      Try sending message with length max+1 from short client to long server
// Exp Result: Message not sent
// ====================================================================================================================

// TODO: Implement test
// ====================================================================================================================
// Desc:       Send message with max length from server to client
// Steps:      Send message with max length from short server to short client
// Exp Result: Message receive by client
// ====================================================================================================================

// TODO: Implement test
// ====================================================================================================================
// Desc:       Send message exceeding max receiving length from server to client
// Steps:      Send message with length max+1 from long server to short client
// Exp Result: Message sent but not received
// ====================================================================================================================

// TODO: Implement test
// ====================================================================================================================
// Desc:       Send message exceeding max sending length from server to client
// Steps:      Try sending message with length max+1 from short server to long client
// Exp Result: Message not sent
// ====================================================================================================================

// ====================================================================================================================
// Desc:       Send long message from client to server
// Steps:      Send long message from client to server (1000000)
// Exp Result: Message received by server
// ====================================================================================================================
TEST_F(TcpGeneral_Test_MsgTransfer, PosTest_ClientToServer_LongMsg)
{
    // Generate message with 1000000 elements of ASCII characters 33 - 126
    string msg;
    for (size_t i = 0; i < 1000000; i += 1)
        msg += static_cast<char>(i % 94 + 33);

    // Send message from client to server
    EXPECT_TRUE(tcpClient.sendMsg(msg));
    this_thread::sleep_for(TestConstants::WAITFOR_MSG_LONG_TCP);

    // Check if message received by server
    vector<TestApi::MessageFromClient> messagesExpected{TestApi::MessageFromClient{clientId, msg}};
    EXPECT_EQ(tcpServer.getBufferedMsg(), messagesExpected);
}

// ====================================================================================================================
// Desc:       Send long message from server to client
// Steps:      Send long message from server to client (1000000)
// Exp Result: Message received by client
// ====================================================================================================================
TEST_F(TcpGeneral_Test_MsgTransfer, PosTest_ServerToClient_LongMsg)
{
    // Generate message with 1000000 elements of ASCII characters 33 - 126
    string msg;
    for (size_t i = 0; i < 1000000; i += 1)
        msg += static_cast<char>(i % 94 + 33);

    // Send message from server to client
    EXPECT_TRUE(tcpServer.sendMsg(clientId, msg));
    this_thread::sleep_for(TestConstants::WAITFOR_MSG_LONG_TCP);

    // Check if message received by client
    vector<string> messagesExpected{msg};
    EXPECT_EQ(tcpClient.getBufferedMsg(), messagesExpected);
}
