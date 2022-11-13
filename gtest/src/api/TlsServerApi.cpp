#include "TlsServerApi.h"

using namespace std;
using namespace TestApi;
using namespace networking;

TlsServerApi_fragmentation::TlsServerApi_fragmentation(size_t messageMaxLen) : TlsServer{'\x00', messageMaxLen} {}
TlsServerApi_fragmentation::~TlsServerApi_fragmentation() {}
TlsServerApi_forwarding::TlsServerApi_forwarding() : TlsServer{TlsServerApi_forwarding::generateForwardingStream} {}
TlsServerApi_forwarding::~TlsServerApi_forwarding() {}
TlsServerApi_fragmentation_ShortMsg::TlsServerApi_fragmentation_ShortMsg() : TlsServerApi_fragmentation{TestConstants::MAXLEN_MSG_SHORT_B} {}
TlsServerApi_fragmentation_ShortMsg::~TlsServerApi_fragmentation_ShortMsg() {}
TlsServerApi_forwarding_ShortMsg::TlsServerApi_forwarding_ShortMsg() : TlsServerApi_forwarding{} {}
TlsServerApi_forwarding_ShortMsg::~TlsServerApi_forwarding_ShortMsg() {}

int TlsServerApi_fragmentation::start(const int port, const string pathToCaCert, const string pathToListenerCert, const string pathToListenerKey)
{
    return TlsServer::start(port, pathToCaCert.c_str(), pathToListenerCert.c_str(), pathToListenerKey.c_str());
}

void TlsServerApi_fragmentation::stop()
{
    TlsServer::stop();
    return;
}

bool TlsServerApi_fragmentation::sendMsg(const int tlsClientId, const std::string &tlsMsg)
{
    return TlsServer::sendMsg(tlsClientId, tlsMsg);
}

vector<MessageFromClient> TlsServerApi_fragmentation::getBufferedMsg()
{
    lock_guard<mutex> lck{bufferedMsg_m};
    return move(bufferedMsg);
}

vector<int> TlsServerApi_fragmentation::getClientIds()
{
    // Get IDs from activeConnections
    vector<int> clientIds;
    lock_guard<mutex> lock(activeConnections_m);
    for (auto &client : activeConnections)
        clientIds.push_back(client.first);
    return clientIds;
}

void TlsServerApi_fragmentation::workOnMessage_TlsServer(const int tlsClientId, const std::string tlsMsgFromClient)
{
    lock_guard<mutex> lck{bufferedMsg_m};
    bufferedMsg.push_back({tlsClientId, move(tlsMsgFromClient)});
    return;
}

void TlsServerApi_fragmentation::workOnClosed_TlsServer(const int tlsClientId)
{
    return;
}

int TlsServerApi_forwarding::start(const int port, const string pathToCaCert, const string pathToListenerCert, const string pathToListenerKey)
{
    return TlsServer::start(port, pathToCaCert.c_str(), pathToListenerCert.c_str(), pathToListenerKey.c_str());
}

void TlsServerApi_forwarding::stop()
{
    TlsServer::stop();
    return;
}

bool TlsServerApi_forwarding::sendMsg(const int tlsClientId, const std::string &tlsMsg)
{
    return TlsServer::sendMsg(tlsClientId, tlsMsg);
}

map<int, string> TlsServerApi_forwarding::getBufferedMsg()
{
    map<int, string> ret;
    for (auto &v : bufferedMsg)
        ret[v.first] = v.second.str();
    bufferedMsg.clear();
    return ret;
}

vector<int> TlsServerApi_forwarding::getClientIds()
{
    // Get IDs from activeConnections
    vector<int> clientIds;
    lock_guard<mutex> lock(activeConnections_m);
    for (auto &client : activeConnections)
        clientIds.push_back(client.first);
    return clientIds;
}

void TlsServerApi_forwarding::workOnMessage_TlsServer(const int tlsClientId, const std::string tlsMsgFromClient)
{
    return;
}

void TlsServerApi_forwarding::workOnClosed_TlsServer(const int tlsClientId)
{
    return;
}
