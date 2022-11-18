#include "TlsServerApi.h"

using namespace std;
using namespace TestApi;
using namespace networking;

TlsServerApi_fragmentation::TlsServerApi_fragmentation(size_t messageMaxLen) : tlsServer{'\x00', messageMaxLen, bind(&TlsServerApi_fragmentation::workOnMessage, this, placeholders::_1, placeholders::_2), bind(&TlsServerApi_fragmentation::workOnClosed, this, placeholders::_1)} {}
TlsServerApi_fragmentation::~TlsServerApi_fragmentation() {}
TlsServerApi_forwarding::TlsServerApi_forwarding() : tlsServer{bind(&TlsServerApi_forwarding::generateForwardingStream, this, placeholders::_1), bind(&TlsServerApi_forwarding::workOnClosed, this, placeholders::_1)} {}
TlsServerApi_forwarding::~TlsServerApi_forwarding() {}
TlsServerApi_fragmentation_ShortMsg::TlsServerApi_fragmentation_ShortMsg() : TlsServerApi_fragmentation{TestConstants::MAXLEN_MSG_SHORT_B} {}
TlsServerApi_fragmentation_ShortMsg::~TlsServerApi_fragmentation_ShortMsg() {}
TlsServerApi_forwarding_ShortMsg::TlsServerApi_forwarding_ShortMsg() : TlsServerApi_forwarding{} {}
TlsServerApi_forwarding_ShortMsg::~TlsServerApi_forwarding_ShortMsg() {}

int TlsServerApi_fragmentation::start(const int port, const std::string pathToCaCert, const std::string pathToListenerCert, const std::string pathToListenerKey)
{
    return tlsServer.start(port, pathToCaCert.c_str(), pathToListenerCert.c_str(), pathToListenerKey.c_str());
}

void TlsServerApi_fragmentation::stop()
{
    tlsServer.stop();
}

bool TlsServerApi_fragmentation::sendMsg(const int tlsClientId, const string &tlsMsg)
{
    return tlsServer.sendMsg(tlsClientId, tlsMsg);
}

vector<MessageFromClient> TlsServerApi_fragmentation::getBufferedMsg()
{
    lock_guard<mutex> lck{bufferedMsg_m};
    return move(bufferedMsg);
}

vector<int> TlsServerApi_fragmentation::getClientIds()
{
    // TODO: Implement
    return {};
}

void TlsServerApi_fragmentation::workOnMessage(const int tlsClientId, const string tlsMsgFromClient)
{
    lock_guard<mutex> lck{bufferedMsg_m};
    bufferedMsg.push_back({tlsClientId, move(tlsMsgFromClient)});
}

void TlsServerApi_fragmentation::workOnClosed(const int) {}

int TlsServerApi_forwarding::start(const int port, const std::string pathToCaCert, const std::string pathToListenerCert, const std::string pathToListenerKey)
{
    return tlsServer.start(port, pathToCaCert.c_str(), pathToListenerCert.c_str(), pathToListenerKey.c_str());
}

void TlsServerApi_forwarding::stop()
{
    tlsServer.stop();
}

bool TlsServerApi_forwarding::sendMsg(const int tlsClientId, const string &tlsMsg)
{
    return tlsServer.sendMsg(tlsClientId, tlsMsg);
}

map<int, string> TlsServerApi_forwarding::getBufferedMsg()
{
    map<int, string> messages;
    for (auto &v : bufferedMsg)
    {
        string msg{v.second->str()};
        if (msg.size())
            messages[v.first] = msg;
    }
    bufferedMsg.clear();
    return messages;
}

vector<int> TlsServerApi_forwarding::getClientIds()
{
    // TODO: Implement
    return {};
}

void TlsServerApi_forwarding::workOnClosed(const int) {}

ostringstream *TlsServerApi_forwarding::generateForwardingStream(int clientId)
{
    bufferedMsg[clientId] = new ostringstream;
    return bufferedMsg[clientId];
}
