#include "TcpClientApi.h"

using namespace std;
using namespace TestApi;
using namespace networking;

TcpClientApi::TcpClientApi(size_t messageMaxLen) : TcpClient{'\x00', messageMaxLen, TestConstants::CONNECTION_TIMEOUT_TCP_ms} {}
TcpClientApi::~TcpClientApi() {}
TcpClientApi_ShortMsg::TcpClientApi_ShortMsg() : TcpClientApi{TestConstants::MAXLEN_MSG_SHORT_B} {}
TcpClientApi_ShortMsg::~TcpClientApi_ShortMsg() {}

int TcpClientApi::start(const std::string &ip, const int port)
{
    return TcpClient::start(ip, port);
}

void TcpClientApi::stop()
{
    TcpClient::stop();
    return;
}

bool TcpClientApi::sendMsg(const std::string &tcpMsg)
{
    return TcpClient::sendMsg(tcpMsg);
}

vector<string> TcpClientApi::getBufferedMsg()
{
    lock_guard<mutex> lck{bufferedMsg_m};
    return move(bufferedMsg);
}

void TcpClientApi::workOnMessage_TcpClient(const std::string tcpMsgFromServer)
{
    lock_guard<mutex> lck{bufferedMsg_m};
    bufferedMsg.push_back(move(tcpMsgFromServer));
    return;
}
