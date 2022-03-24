#pragma once
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
#elif __unix__
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <netdb.h>
    #include <arpa/inet.h>
#endif

#include <string>
#include <list>
#include "interface.h"
#include "type_traits_frame.h"

class TcpClient : public IModelObservable
{
    std::string m_servername;
    u_short m_port;
#ifdef _WIN32    
    WSADATA ws_data;
    SOCKET m_soket;
    HOSTENT *hst; 
#elif __unix__
    int m_soket;
    struct hostent *hst;
#endif
    sockaddr_in m_servInfo;
       
    mutable std::list<std::weak_ptr<IViewObserver>> __observer;

public:
    TcpClient(const std::string& serveraddr, u_short port);
    
    TcpClient(const TcpClient& other) = delete;
    TcpClient& operator=(const TcpClient& other) = delete;

    void addObserver(std::shared_ptr<IViewObserver>) override;
    void removeObserver(std::shared_ptr<IViewObserver>) override;
    void notify(const std::string& message, const Frame* frame = nullptr) const override;
    
    bool StartConnect(); 
    bool sendFrame(Frame* frame);
    std::pair<bool, std::unique_ptr<Frame>> recvAnswer(int len);
    void startUpsocket();
    bool getip();

    ~TcpClient();
};

