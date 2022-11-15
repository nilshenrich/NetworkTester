#ifndef TCP_SERVER_API_H_
#define TCP_SERVER_API_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <mutex>

#include "TcpServer.h"
#include "TestDefines.h"

namespace TestApi
{
    class TcpServerApi_fragmentation : private networking::TcpServer
    {
    public:
        TcpServerApi_fragmentation(size_t messageMaxLen = TestConstants::MAXLEN_MSG_B);
        virtual ~TcpServerApi_fragmentation();

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
         * @return std::vector<MessageFromClient> Vector of buffered messages
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
        std::mutex bufferedMsg_m;
    };

    class TcpServerApi_forwarding : private networking::TcpServer
    {
    public:
        TcpServerApi_forwarding();
        virtual ~TcpServerApi_forwarding();

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
         * @return std::map<int, std::string> Vector of buffered messages
         */
        std::map<int, std::string> getBufferedMsg();

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

        /**
         * @brief Generate an output stream to a string for each client
         *
         * @param clientId
         * @return std::ostringstream*
         */
        static std::ostringstream *generateForwardingStream(int clientId);

        // Buffered messages
        // TODO: Bad practice having static
        static std::map<int, std::ostringstream *> bufferedMsg;
    };

    class TcpServerApi_fragmentation_ShortMsg : public TcpServerApi_fragmentation
    {
    public:
        TcpServerApi_fragmentation_ShortMsg();
        virtual ~TcpServerApi_fragmentation_ShortMsg();
    };

    class TcpServerApi_forwarding_ShortMsg : public TcpServerApi_forwarding
    {
    public:
        TcpServerApi_forwarding_ShortMsg();
        virtual ~TcpServerApi_forwarding_ShortMsg();
    };

} // namespace TestApi

#endif // TCP_SERVER_API_H_
