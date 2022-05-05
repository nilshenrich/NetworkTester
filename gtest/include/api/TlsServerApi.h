#ifndef TLS_SERVER_API_H_
#define TLS_SERVER_API_H_

#include <iostream>
#include <string>
#include <vector>
#include <mutex>

#include "TlsServer.h"
#include "TestDefines.h"

namespace TestApi
{
    class TlsServerApi : private networking::TlsServer
    {
    public:
        TlsServerApi();
        virtual ~TlsServerApi();

        /**
         * @brief Start TLS server
         *
         * @param port TLS port to listen on
         * @return int NETWORKLISTENER_START_OK if successful, other if failed
         */
        int start(const int port, const std::string pathToCaCert = KeyPaths::CaCert, const std::string pathToListenerCert = KeyPaths::ListenerCert, const std::string pathToListenerKey = KeyPaths::ListenerKey);

        /**
         * @brief Stop TLS server
         */
        void stop();

        /**
         * @brief Send message to TLS client
         *
         * @param tlsClientId TLS client ID
         * @param tlsMsg Message to send
         * @return bool true if successful, false if failed
         */
        bool sendMsg(const int tlsClientId, const std::string &tlsMsg);

        /**
         * @brief Get buffered message from TLS clients and clear buffer
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
         * @param tlsClientId ID des Clients
         * @param tlsMsgFromClient Nachricht vom Client
         */
        void workOnMessage_TlsServer(const int tlsClientId, const std::string tlsMsgFromClient) override;

        /**
         * @brief Wenn ein Client geschlossen wurde, diesen aus der Liste entfernen
         *
         * @param tcpClientId ID des Clients
         */
        void workOnClosed_TlsServer(const int tlsClientId) override;

        // Buffered messages
        std::vector<MessageFromClient> bufferedMsg;
    };
}

#endif // TLS_SERVER_API_H_
