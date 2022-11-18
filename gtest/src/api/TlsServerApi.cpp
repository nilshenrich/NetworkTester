#include "TlsServerApi.h"

using namespace std;
using namespace TestApi;
using namespace networking;

TlsServerApi_fragmentation::TlsServerApi_fragmentation(size_t messageMaxLen) {}
TlsServerApi_fragmentation::~TlsServerApi_fragmentation() {}
TlsServerApi_forwarding::TlsServerApi_forwarding() {}
TlsServerApi_forwarding::~TlsServerApi_forwarding() {}
TlsServerApi_fragmentation_ShortMsg::TlsServerApi_fragmentation_ShortMsg() : TlsServerApi_fragmentation{TestConstants::MAXLEN_MSG_SHORT_B} {}
TlsServerApi_fragmentation_ShortMsg::~TlsServerApi_fragmentation_ShortMsg() {}
TlsServerApi_forwarding_ShortMsg::TlsServerApi_forwarding_ShortMsg() : TlsServerApi_forwarding{} {}
TlsServerApi_forwarding_ShortMsg::~TlsServerApi_forwarding_ShortMsg() {}
