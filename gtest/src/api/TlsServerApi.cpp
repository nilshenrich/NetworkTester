#include "TlsServerApi.h"

using namespace std;
using namespace TestApi;
using namespace networking;

TlsServerApi::TlsServerApi() : TlsServer{'\x00'} {}
TlsServerApi::~TlsServerApi() {}

int TlsServerApi::start(const int port)
{
    return TlsServer::start(port, KeyPaths::CaCert.c_str(), KeyPaths::ServerCert.c_str(), KeyPaths::ServerKey.c_str());
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
