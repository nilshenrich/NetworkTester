#include "TlsServerApi.h"

using namespace std;
using namespace TestApi;
using namespace networking;

TlsServerApi::TlsServerApi(size_t messageMaxLen) : TlsServer{'\x00', messageMaxLen} {}
TlsServerApi::~TlsServerApi() {}
TlsServerApi_ShortMsg::TlsServerApi_ShortMsg() : TlsServerApi{TestConstants::MAXLEN_MSG_SHORT_B} {}
TlsServerApi_ShortMsg::~TlsServerApi_ShortMsg() {}

int TlsServerApi::start(const int port, const string pathToCaCert, const string pathToListenerCert, const string pathToListenerKey)
{
    return TlsServer::start(port, pathToCaCert.c_str(), pathToListenerCert.c_str(), pathToListenerKey.c_str());
}

void TlsServerApi::stop()
{
    TlsServer::stop();
    return;
}

bool TlsServerApi::sendMsg(const int tlsClientId, const std::string &tlsMsg)
{
    return TlsServer::sendMsg(tlsClientId, tlsMsg);
}

vector<MessageFromClient> TlsServerApi::getBufferedMsg()
{
    return move(bufferedMsg);
}

vector<int> TlsServerApi::getClientIds()
{
    // Get IDs from activeConnections
    vector<int> clientIds;
    lock_guard<mutex> lock(activeConnections_m);
    for (auto &client : activeConnections)
        clientIds.push_back(client.first);
    return clientIds;
}

void TlsServerApi::workOnMessage_TlsServer(const int tlsClientId, const std::string tlsMsgFromClient)
{
    bufferedMsg.push_back({tlsClientId, move(tlsMsgFromClient)});
    return;
}

void TlsServerApi::workOnClosed_TlsServer(const int tlsClientId)
{
    return;
}
