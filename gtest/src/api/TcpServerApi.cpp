#include "TcpServerApi.h"

using namespace std;
using namespace TestApi;
using namespace networking;

TcpServerApi_fragmentation::TcpServerApi_fragmentation(size_t messageMaxLen) : TcpServer{'\x00', messageMaxLen} {}
TcpServerApi_fragmentation::~TcpServerApi_fragmentation() {}
TcpServerApi_forwarding::TcpServerApi_forwarding() : TcpServer{&TcpServerApi_forwarding::generateForwardingStream} {}
TcpServerApi_forwarding::~TcpServerApi_forwarding() {}
TcpServerApi_fragmentation_ShortMsg::TcpServerApi_fragmentation_ShortMsg() : TcpServerApi_fragmentation{TestConstants::MAXLEN_MSG_SHORT_B} {}
TcpServerApi_fragmentation_ShortMsg::~TcpServerApi_fragmentation_ShortMsg() {}
TcpServerApi_forwarding_ShortMsg::TcpServerApi_forwarding_ShortMsg() : TcpServerApi_forwarding{} {}
TcpServerApi_forwarding_ShortMsg::~TcpServerApi_forwarding_ShortMsg() {}

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

int TcpServerApi_forwarding::start(const int port)
{
    return TcpServer::start(port);
}

void TcpServerApi_forwarding::stop()
{
    TcpServer::stop();
    return;
}

bool TcpServerApi_forwarding::sendMsg(const int tcpClientId, const std::string &tcpMsg)
{
    return TcpServer::sendMsg(tcpClientId, tcpMsg);
}

map<int, string> TcpServerApi_forwarding::getBufferedMsg()
{
    map<int, string> ret;
    for (auto &v : bufferedMsg)
    {
        string msg{v.second->str()};
        if (msg.size())
            ret[v.first] = msg;
    }
    bufferedMsg.clear();
    return ret;
}

vector<int> TcpServerApi_forwarding::getClientIds()
{
    // Get IDs from activeConnections
    vector<int> clientIds;
    lock_guard<mutex> lck(activeConnections_m);
    for (auto &client : activeConnections)
        clientIds.push_back(client.first);
    return clientIds;
}

void TcpServerApi_forwarding::workOnMessage_TcpServer(const int tcpClientId, const std::string tcpMsgFromClient)
{
    return;
}

void TcpServerApi_forwarding::workOnClosed_TcpServer(const int tcpClientId)
{
    return;
}

map<int, ostringstream *> TcpServerApi_forwarding::bufferedMsg;
ostringstream *TcpServerApi_forwarding::generateForwardingStream(int clientId)
{
    // If stream already exists, just return pointer to
    // If stream doesn't exist yet, create it and return pointer to
    if (bufferedMsg.find(clientId) == bufferedMsg.end())
        bufferedMsg[clientId] = new ostringstream{ios_base::ate};
    return bufferedMsg[clientId];
}
