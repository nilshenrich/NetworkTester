#ifndef TLS_CLIENT_API_H_
#define TLS_CLIENT_API_H_

#include <iostream>
#include <string>
#include <vector>
#include <mutex>

#include "TlsClient.h"
#include "TestDefines.h"

namespace TestApi
{
    class TlsClientApi_fragmentation : private networking::TlsClient
    {
    public:
        TlsClientApi_fragmentation(size_t messageMaxLen = TestConstants::MAXLEN_MSG_B);
        virtual ~TlsClientApi_fragmentation();

        /**
         * @brief Connect to TLS server
         *
         * @param ip IP address of TLS server
         * @param port TLS port of TLS server
         * @return int TLSCLIENT_CONNECT_OK if successful, other if failed
         */
        int start(const std::string &ip, const int port, const std::string pathToCaCert = KeyPaths::CaCert, const std::string pathToClientCert = KeyPaths::ClientCert, const std::string pathToClientKey = KeyPaths::ClientKey);

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
        std::mutex bufferedMsg_m;
    };

    class TlsClientApi_fragmentation_ShortMsg : public TlsClientApi_fragmentation
    {
    public:
        TlsClientApi_fragmentation_ShortMsg();
        virtual ~TlsClientApi_fragmentation_ShortMsg();
    };

} // namespace TestApi

#endif // TLS_CLIENT_API_H_
