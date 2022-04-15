#include <gtest/gtest.h>

#include "TcpServerApi.h"

namespace Test
{
    class TcpServer_Test_Start : public testing::Test
    {
    public:
        TcpServer_Test_Start();
        virtual ~TcpServer_Test_Start();

    protected:
        /**
         * @brief Stop server
         */
        void TearDown() override;

        // TCP Server
        TestApi::TcpServerApi tcpServer{};
    };
}
