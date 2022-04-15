#ifndef TLS_CLIENT_API_H_
#define TLS_CLIENT_API_H_

#include <iostream>
#include <string>
#include <vector>

#include "NetworkClient/TlsClient.h"
#include "TestDefines.h"

namespace TestApi
{
    class TlsClientApi : private networking::TlsClient
    {
    public:
        TlsClientApi();
        virtual ~TlsClientApi();

        /**
         * @brief Connect to TLS server
         *
         * @param ip IP address of TLS server
         * @param port TLS port of TLS server
         * @return int TLSCLIENT_CONNECT_OK if successful, other if failed
         */
        int start(const std::string &ip, const int port);

        /**
         * @brief Disconnect from TLS server
         */
        void stop();

        /**
         * @brief Send message to TLS server
         *
         * @param tcpMsg Message to send
         * @return bool true if successful, false if failed
         */
        bool sendMsg(const std::string &tcpMsg);

        /**
         * @brief Get buffered message from TLS server and clear buffer
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
        void workOnMessage_TlsClient(const std::string tcpMsgFromServer) override;

        // Buffered messages
        std::vector<std::string> bufferedMsg;
    };
} // namespace TestApi

#endif // TLS_CLIENT_API_H_
