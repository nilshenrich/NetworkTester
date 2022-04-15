#ifndef TCP_SERVER_API_H_
#define TCP_SERVER_API_H_

#include <iostream>
#include <string>
#include <vector>

#include "NetworkListener/TcpServer.h"
#include "TestDefines.h"

namespace TestApi
{
    class TcpServerApi : private networking::TcpServer
    {
    public:
        TcpServerApi();
        virtual ~TcpServerApi();

        /**
         * @brief Start TCP server
         *
         * @param port TCP port to listen on
         * @return int NETWORKLISTENER_START_OK if successful, other if failed
         */
        int start(const int port);

        /**
         * @brief Stop TCP server
         */
        void stop();

        /**
         * @brief Send message to TCP client
         *
         * @param tcpClientId TCP client ID
         * @param tcpMsg Message to send
         * @return bool true if successful, false if failed
         */
        bool sendMsg(const int tcpClientId, const std::string &tcpMsg);

        /**
         * @brief Get buffered message from TCP clients and clear buffer
         *
         * @return std::vector<std::string> Vector of buffered messages
         */
        std::vector<MessageFromClient> getBufferedMsg();

        /**
         * @brief Get IDs of all connected clients
         *
         * @return std::vector<int> Vector of client IDs
         */
        std::vector<int> getClientIds();

    private:
        /**
         * @brief Wenn eine Nachricht vom Client empfangen wurde, diese puffern
         *
         * @param tcpClientId ID des Clients
         * @param tcpMsgFromClient Nachricht vom Client
         */
        void workOnMessage_TcpServer(const int tcpClientId, const std::string tcpMsgFromClient) override;

        /**
         * @brief Wenn ein Client geschlossen wurde, diesen aus der Liste entfernen
         *
         * @param tcpClientId ID des Clients
         */
        void workOnClosed_TcpServer(const int tcpClientId) override;

        // Buffered messages
        std::vector<MessageFromClient> bufferedMsg;
    };
} // namespace TestApi

#endif // TCP_SERVER_API_H_
