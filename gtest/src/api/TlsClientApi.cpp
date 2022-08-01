#include "TlsClientApi.h"

using namespace std;
using namespace TestApi;
using namespace networking;

TlsClientApi::TlsClientApi(size_t messageMaxLen) : TlsClient{'\x00', messageMaxLen, TestConstants::CONNECTION_TIMEOUT_TLS_ms} {}
TlsClientApi::~TlsClientApi() {}
TlsClientApi_ShortMsg::TlsClientApi_ShortMsg() : TlsClientApi{TestConstants::MAXLEN_MSG_SHORT_B} {}
TlsClientApi_ShortMsg::~TlsClientApi_ShortMsg() {}

int TlsClientApi::start(const std::string &ip, const int port, string pathToCaCert, string pathToClientCert, string pathToClientKey)
{
    return TlsClient::start(ip, port, pathToCaCert.c_str(), pathToClientCert.c_str(), pathToClientKey.c_str());
}

void TlsClientApi::stop()
{
    TlsClient::stop();
    return;
}

bool TlsClientApi::sendMsg(const std::string &tlsMsg)
{
    return TlsClient::sendMsg(tlsMsg);
}

vector<string> TlsClientApi::getBufferedMsg()
{
    return move(bufferedMsg);
}

void TlsClientApi::workOnMessage_TlsClient(const std::string tlsMsgFromServer)
{
    bufferedMsg.push_back(move(tlsMsgFromServer));
    return;
}
