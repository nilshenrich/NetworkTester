#include "TcpClientApi.h"

using namespace std;
using namespace TestApi;
using namespace networking;

TcpClientApi_fragmentation::TcpClientApi_fragmentation(size_t messageMaxLen) : TcpClient{'\x00', messageMaxLen, TestConstants::CONNECTION_TIMEOUT_TCP_ms} {}
TcpClientApi_fragmentation::~TcpClientApi_fragmentation() {}
TcpClientApi_fragmentation_ShortMsg::TcpClientApi_fragmentation_ShortMsg() : TcpClientApi_fragmentation{TestConstants::MAXLEN_MSG_SHORT_B} {}
TcpClientApi_fragmentation_ShortMsg::~TcpClientApi_fragmentation_ShortMsg() {}

int TcpClientApi_fragmentation::start(const std::string &ip, const int port)
{
    return TcpClient::start(ip, port);
}

void TcpClientApi_fragmentation::stop()
{
    TcpClient::stop();
    return;
}

bool TcpClientApi_fragmentation::sendMsg(const std::string &tcpMsg)
{
    return TcpClient::sendMsg(tcpMsg);
}

vector<string> TcpClientApi_fragmentation::getBufferedMsg()
{
    lock_guard<mutex> lck{bufferedMsg_m};
    return move(bufferedMsg);
}

void TcpClientApi_fragmentation::workOnMessage_TcpClient(const std::string tcpMsgFromServer)
{
    lock_guard<mutex> lck{bufferedMsg_m};
    bufferedMsg.push_back(move(tcpMsgFromServer));
    return;
}
