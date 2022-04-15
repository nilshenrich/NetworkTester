#ifndef TCP_CLIENT_API_H_
#define TCP_CLIENT_API_H_

#include <iostream>
#include <string>
#include <vector>

#include "NetworkClient/TcpClient.h"
#include "TestDefines.h"

namespace TestApi
{
    class TcpClientApi : private networking::TcpClient
    {
    public:
        TcpClientApi();
        virtual ~TcpClientApi();

        /**
         * @brief Connect to TCP server
         *
         * @param ip IP address of TCP server
         * @param port TCP port of TCP server
         * @return int NETWORKCLIENT_CONNECT_OK if successful, other if failed
         */
        int start(const std::string &ip, const int port);

        /**
         * @brief Disconnect from TCP server
         */
        void stop();

        /**
         * @brief Send message to TCP server
         *
         * @param tcpMsg Message to send
         * @return bool true if successful, false if failed
         */
        bool sendMsg(const std::string &tcpMsg);

        /**
         * @brief Get buffered message from TCP server and clear buffer
         *
         * @return std::vector<std::string> Vector of buffered messages
         */
        std::vector<std::string> getBufferedMsg();

    private:
        /**
         * @brief Wenn eine Nachricht vom Server empfangen wurde, diese puffern
         *
         * @param tcpMsgFromServer Nachricht vom Server
         */
        void workOnMessage_TcpClient(const std::string tcpMsgFromServer) override;

        // Buffered messages
        std::vector<std::string> bufferedMsg;
    };
} // namespace TestApi

#endif // TCP_CLIENT_API_H_
