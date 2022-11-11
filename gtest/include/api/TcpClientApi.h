#ifndef TCP_CLIENT_API_H_
#define TCP_CLIENT_API_H_

#include <iostream>
#include <string>
#include <vector>
#include <mutex>

#include "TcpClient.h"
#include "TestDefines.h"

namespace TestApi
{
    class TcpClientApi_fragmentation : private networking::TcpClient
    {
    public:
        TcpClientApi_fragmentation(size_t messageMaxLen = TestConstants::MAXLEN_MSG_B);
        virtual ~TcpClientApi_fragmentation();

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
        std::mutex bufferedMsg_m;
    };

    class TcpClientApi_forwarding : private networking::TcpClient
    {
    public:
        TcpClientApi_forwarding();
        virtual ~TcpClientApi_forwarding();

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
         * @return std::string Vector of buffered messages
         */
        std::string getBufferedMsg();

    private:
        /**
         * @brief Wenn eine Nachricht vom Server empfangen wurde, diese puffern
         *
         * @param tcpMsgFromServer Nachricht vom Server
         */
        void workOnMessage_TcpClient(const std::string tcpMsgFromServer) override;

        // Buffered messages
        std::string bufferedMsg;
        std::mutex bufferedMsg_m;
    };

    class TcpClientApi_fragmentation_ShortMsg : public TcpClientApi_fragmentation
    {
    public:
        TcpClientApi_fragmentation_ShortMsg();
        virtual ~TcpClientApi_fragmentation_ShortMsg();
    };

    class TcpClientApi_forwarding_ShortMsg : public TcpClientApi_forwarding
    {
    public:
        TcpClientApi_forwarding_ShortMsg();
        virtual ~TcpClientApi_forwarding_ShortMsg();
    };

} // namespace TestApi

#endif // TCP_CLIENT_API_H_
