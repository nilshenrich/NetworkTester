#include "TcpServerApi.h"

using namespace std;
using namespace TestApi;
using namespace networking;

TcpServerApi_fragmentation::TcpServerApi_fragmentation(size_t messageMaxLen) : tcpServer{'\x00', messageMaxLen, bind(&TcpServerApi_fragmentation::workOnMessage, this, placeholders::_1, placeholders::_2), bind(&TcpServerApi_fragmentation::workOnClosed, this, placeholders::_1)} {}
TcpServerApi_fragmentation::~TcpServerApi_fragmentation() {}
TcpServerApi_forwarding::TcpServerApi_forwarding() : tcpServer{bind(&TcpServerApi_forwarding::generateForwardingStream, this, placeholders::_1), bind(&TcpServerApi_forwarding::workOnClosed, this, placeholders::_1)} {}
TcpServerApi_forwarding::~TcpServerApi_forwarding() {}
TcpServerApi_fragmentation_ShortMsg::TcpServerApi_fragmentation_ShortMsg() : TcpServerApi_fragmentation{TestConstants::MAXLEN_MSG_SHORT_B} {}
TcpServerApi_fragmentation_ShortMsg::~TcpServerApi_fragmentation_ShortMsg() {}
TcpServerApi_forwarding_ShortMsg::TcpServerApi_forwarding_ShortMsg() : TcpServerApi_forwarding{} {}
TcpServerApi_forwarding_ShortMsg::~TcpServerApi_forwarding_ShortMsg() {}

int TcpServerApi_fragmentation::start(const int port)
{
    return tcpServer.start(port);
}

void TcpServerApi_fragmentation::stop()
{
    tcpServer.stop();
}

bool TcpServerApi_fragmentation::sendMsg(const int tcpClientId, const string &tcpMsg)
{
    return tcpServer.sendMsg(tcpClientId, tcpMsg);
}

vector<MessageFromClient> TcpServerApi_fragmentation::getBufferedMsg()
{
    lock_guard<mutex> lck{bufferedMsg_m};
    return move(bufferedMsg);
}

vector<int> TcpServerApi_fragmentation::getClientIds()
{
    return tcpServer.getAllClientIds();
}

void TcpServerApi_fragmentation::workOnMessage(const int tcpClientId, const string tcpMsgFromClient)
{
    lock_guard<mutex> lck{bufferedMsg_m};
    bufferedMsg.push_back({tcpClientId, move(tcpMsgFromClient)});
}

void TcpServerApi_fragmentation::workOnClosed(const int) {}

int TcpServerApi_forwarding::start(const int port)
{
    return tcpServer.start(port);
}

void TcpServerApi_forwarding::stop()
{
    tcpServer.stop();
}

bool TcpServerApi_forwarding::sendMsg(const int tcpClientId, const string &tcpMsg)
{
    return tcpServer.sendMsg(tcpClientId, tcpMsg);
}

map<int, string> TcpServerApi_forwarding::getBufferedMsg()
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

vector<int> TcpServerApi_forwarding::getClientIds()
{
    return tcpServer.getAllClientIds();
}

void TcpServerApi_forwarding::workOnClosed(const int) {}

ostringstream *TcpServerApi_forwarding::generateForwardingStream(int clientId)
{
    bufferedMsg[clientId] = new ostringstream;
    return bufferedMsg[clientId];
}
