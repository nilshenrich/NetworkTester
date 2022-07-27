#include "TcpClientApi.h"

using namespace std;
using namespace TestApi;
using namespace networking;

TcpClientApi::TcpClientApi() : TcpClient{'\x00', TestConstants::MAXLEN_MSG_B, TestConstants::CONNECTION_TIMEOUT_TCP_ms} {}
TcpClientApi::~TcpClientApi() {}

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
    return move(bufferedMsg);
}

void TcpClientApi::workOnMessage_TcpClient(const std::string tcpMsgFromServer)
{
    bufferedMsg.push_back(move(tcpMsgFromServer));
    return;
}
