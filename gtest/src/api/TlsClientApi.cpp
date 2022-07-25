#include "TlsClientApi.h"

using namespace std;
using namespace TestApi;
using namespace networking;

TlsClientApi::TlsClientApi() : TlsClient{'\x00'} {}
TlsClientApi::~TlsClientApi() {}

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
    lock_guard<mutex> lck{bufferedMsg_m};
    return move(bufferedMsg);
}

void TlsClientApi::workOnMessage_TlsClient(const std::string tlsMsgFromServer)
{
    lock_guard<mutex> lck{bufferedMsg_m};
    bufferedMsg.push_back(move(tlsMsgFromServer));
    return;
}
