#include "TcpServerApi.h"

using namespace std;
using namespace TestApi;
using namespace networking;

TcpServerApi_fragmentation::TcpServerApi_fragmentation(size_t messageMaxLen) {}
TcpServerApi_fragmentation::~TcpServerApi_fragmentation() {}
TcpServerApi_forwarding::TcpServerApi_forwarding() {}
TcpServerApi_forwarding::~TcpServerApi_forwarding() {}
TcpServerApi_fragmentation_ShortMsg::TcpServerApi_fragmentation_ShortMsg() : TcpServerApi_fragmentation{TestConstants::MAXLEN_MSG_SHORT_B} {}
TcpServerApi_fragmentation_ShortMsg::~TcpServerApi_fragmentation_ShortMsg() {}
TcpServerApi_forwarding_ShortMsg::TcpServerApi_forwarding_ShortMsg() : TcpServerApi_forwarding{} {}
TcpServerApi_forwarding_ShortMsg::~TcpServerApi_forwarding_ShortMsg() {}
