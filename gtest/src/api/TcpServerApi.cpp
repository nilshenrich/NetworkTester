#include "TcpServerApi.h"

using namespace std;
using namespace TestApi;
using namespace networking;

TcpServerApi::TcpServerApi() : TcpServer{'\x00'} {}
TcpServerApi::~TcpServerApi() {}

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
    bufferedMsg.push_back({tcpClientId, move(tcpMsgFromClient)});
    return;
}

void TcpServerApi::workOnClosed_TcpServer(const int tcpClientId)
{
    return;
}
