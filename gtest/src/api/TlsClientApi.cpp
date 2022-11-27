#include "TlsClientApi.h"

using namespace std;
using namespace TestApi;
using namespace networking;

TlsClientApi_fragmentation::TlsClientApi_fragmentation(size_t messageMaxLen) : tlsClient{'\x00', bind(&TlsClientApi_fragmentation::workOnMessage, this, placeholders::_1), TestConstants::CONNECTION_TIMEOUT_TLS_ms, messageMaxLen} {}
TlsClientApi_fragmentation::~TlsClientApi_fragmentation() {}
TlsClientApi_forwarding::TlsClientApi_forwarding() : tlsClient{bufferedMsg_os} {}
TlsClientApi_forwarding::~TlsClientApi_forwarding() {}
TlsClientApi_fragmentation_ShortMsg::TlsClientApi_fragmentation_ShortMsg() : TlsClientApi_fragmentation{TestConstants::MAXLEN_MSG_SHORT_B} {}
TlsClientApi_fragmentation_ShortMsg::~TlsClientApi_fragmentation_ShortMsg() {}
TlsClientApi_forwarding_ShortMsg::TlsClientApi_forwarding_ShortMsg() : TlsClientApi_forwarding{} {}
TlsClientApi_forwarding_ShortMsg::~TlsClientApi_forwarding_ShortMsg() {}

int TlsClientApi_fragmentation::start(const std::string &ip, const int port, string pathToCaCert, string pathToClientCert, string pathToClientKey)
{
    return tlsClient.start(ip, port, pathToCaCert.c_str(), pathToClientCert.c_str(), pathToClientKey.c_str());
}

void TlsClientApi_fragmentation::stop()
{
    tlsClient.stop();
    return;
}

bool TlsClientApi_fragmentation::sendMsg(const std::string &tlsMsg)
{
    return tlsClient.sendMsg(tlsMsg);
}

vector<string> TlsClientApi_fragmentation::getBufferedMsg()
{
    lock_guard<mutex> lck{bufferedMsg_m};
    return move(bufferedMsg);
}

void TlsClientApi_fragmentation::workOnMessage(const std::string tlsMsgFromServer)
{
    lock_guard<mutex> lck{bufferedMsg_m};
    bufferedMsg.push_back(move(tlsMsgFromServer));
    return;
}

int TlsClientApi_forwarding::start(const std::string &ip, const int port, string pathToCaCert, string pathToClientCert, string pathToClientKey)
{
    return tlsClient.start(ip, port, pathToCaCert.c_str(), pathToClientCert.c_str(), pathToClientKey.c_str());
}

void TlsClientApi_forwarding::stop()
{
    tlsClient.stop();
    return;
}

bool TlsClientApi_forwarding::sendMsg(const std::string &tlsMsg)
{
    return tlsClient.sendMsg(tlsMsg);
}

string TlsClientApi_forwarding::getBufferedMsg()
{
    return bufferedMsg_os.str();
}
