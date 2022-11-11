#include "TcpServerApi.h"

using namespace std;
using namespace TestApi;
using namespace networking;

TcpServerApi_fragmentation::TcpServerApi_fragmentation(size_t messageMaxLen) : TcpServer{'\x00', messageMaxLen} {}
TcpServerApi_fragmentation::~TcpServerApi_fragmentation() {}
TcpServerApi_fragmentation_ShortMsg::TcpServerApi_fragmentation_ShortMsg() : TcpServerApi_fragmentation{TestConstants::MAXLEN_MSG_SHORT_B} {}
TcpServerApi_fragmentation_ShortMsg::~TcpServerApi_fragmentation_ShortMsg() {}

int TcpServerApi_fragmentation::start(const int port)
{
    return TcpServer::start(port);
}

void TcpServerApi_fragmentation::stop()
{
    TcpServer::stop();
    return;
}

bool TcpServerApi_fragmentation::sendMsg(const int tcpClientId, const std::string &tcpMsg)
{
    return TcpServer::sendMsg(tcpClientId, tcpMsg);
}

vector<MessageFromClient> TcpServerApi_fragmentation::getBufferedMsg()
{
    lock_guard<mutex> lck{bufferedMsg_m};
    return move(bufferedMsg);
}

vector<int> TcpServerApi_fragmentation::getClientIds()
{
    // Get IDs from activeConnections
    vector<int> clientIds;
    lock_guard<mutex> lck(activeConnections_m);
    for (auto &client : activeConnections)
        clientIds.push_back(client.first);
    return clientIds;
}

void TcpServerApi_fragmentation::workOnMessage_TcpServer(const int tcpClientId, const std::string tcpMsgFromClient)
{
    lock_guard<mutex> lck{bufferedMsg_m};
    bufferedMsg.push_back({tcpClientId, move(tcpMsgFromClient)});
    return;
}

void TcpServerApi_fragmentation::workOnClosed_TcpServer(const int tcpClientId)
{
    return;
}
