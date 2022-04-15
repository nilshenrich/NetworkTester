#include "TlsClientApi.h"

using namespace std;
using namespace TestApi;
using namespace networking;

TlsClientApi::TlsClientApi() : TlsClient{'\x00'} {}
TlsClientApi::~TlsClientApi() {}

int TlsClientApi::start(const std::string &ip, const int port)
{
    return TlsClient::start(ip, port, KeyPaths::CaCert.c_str(), KeyPaths::ClientCert.c_str(), KeyPaths::ClientKey.c_str());
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
