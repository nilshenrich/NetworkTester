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
    class TcpServerApi_fragmentation
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
         * @brief Buffer incoming messages
         *
         * @param tcpClientId ID des Clients
         * @param tcpMsgFromClient Nachricht vom Client
         */
        void workOnMessage(const int tcpClientId, const std::string tcpMsgFromClient);

        /**
         * @brief Remove closed connections from buffer
         *
         * @param tcpClientId ID des Clients
         */
        void workOnClosed(const int tcpClientId);

        // TCP server
        networking::TcpServer tcpServer;

        // Buffered messages
        std::vector<MessageFromClient> bufferedMsg;
        std::mutex bufferedMsg_m;
    };

    class TcpServerApi_forwarding
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
         * @brief Remove closed connections from buffer
         *
         * @param tcpClientId ID des Clients
         */
        void workOnClosed(const int tcpClientId);

        // TCP server
        networking::TcpServer tcpServer;

        /**
         * @brief Generate an output stream to a string for each client
         *
         * @param clientId
         * @return std::ostringstream*
         */
        std::ostringstream *generateForwardingStream(int clientId);

        // Buffered messages
        std::map<int, std::ostringstream *> bufferedMsg;
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
