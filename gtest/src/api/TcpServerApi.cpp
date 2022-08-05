#include "TcpServerApi.h"

using namespace std;
using namespace TestApi;
using namespace networking;

TcpServerApi::TcpServerApi(size_t messageMaxLen) : TcpServer{'\x00', messageMaxLen} {}
TcpServerApi::~TcpServerApi() {}
TcpServerApi_ShortMsg::TcpServerApi_ShortMsg() : TcpServerApi{TestConstants::MAXLEN_MSG_SHORT_B} {}
TcpServerApi_ShortMsg::~TcpServerApi_ShortMsg() {}

int TcpServerApi::start(const int port)
{
    return TcpServer::start(port);
}

void TcpServerApi::stop()
{
    TcpServer::stop();
    return;
}

bool TcpServerApi::sendMsg(const int tcpClientId, const std::string &tcpMsg)
{
    return TcpServer::sendMsg(tcpClientId, tcpMsg);
}

vector<MessageFromClient> TcpServerApi::getBufferedMsg()
{
    lock_guard<mutex> lck{bufferedMsg_m};
    return move(bufferedMsg);
}

vector<int> TcpServerApi::getClientIds()
{
    // Get IDs from activeConnections
    vector<int> clientIds;
    lock_guard<mutex> lck(activeConnections_m);
    for (auto &client : activeConnections)
        clientIds.push_back(client.first);
    return clientIds;
}

void TcpServerApi::workOnMessage_TcpServer(const int tcpClientId, const std::string tcpMsgFromClient)
{
    lock_guard<mutex> lck{bufferedMsg_m};
    bufferedMsg.push_back({tcpClientId, move(tcpMsgFromClient)});
    return;
}

void TcpServerApi::workOnClosed_TcpServer(const int tcpClientId)
{
    return;
}
