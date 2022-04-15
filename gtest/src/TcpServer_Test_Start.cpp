#include "TcpServer_Test_Start.h"

using namespace std;
using namespace Test;
using namespace networking;

TcpServer_Test_Start::TcpServer_Test_Start() {}
TcpServer_Test_Start::~TcpServer_Test_Start() {}

void TcpServer_Test_Start::SetUp()
{
    // Get free TCP port
    port = HelperFunctions::getFreePort();
    return;
}

void TcpServer_Test_Start::TearDown()
{
    tcpServer.stop();
    return;
}

TEST_F(TcpServer_Test_Start, PosTest)
{
    EXPECT_EQ(tcpServer.start(port), NETWORKLISTENER_START_OK);
}
