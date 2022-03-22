#pragma once
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <list>
#include "interface.h"
#include "type_traits_frame.h"

class TcpClient : public IModelObservable
{
    std::string m_servername;
    u_short m_port;
    WSADATA ws_data;
    SOCKET m_soket;
    sockaddr_in m_servInfo;
    HOSTENT *hst;    
    mutable std::list<std::weak_ptr<IViewObserver>> __observer;

public:
    TcpClient(const std::string& serveraddr, u_short port);
    
    TcpClient(const TcpClient& other) = delete;
    TcpClient& operator=(const TcpClient& other) = delete;

    void addObserver(std::shared_ptr<IViewObserver>) override;
    void removeObserver(std::shared_ptr<IViewObserver>) override;
    void notify(const std::string& message, const Frame& frame = Frame()) const override;
    
    bool StartConnect(); 
    bool sendFrame(const Frame& frame) const;
    std::pair<bool, Frame> recvAnswer();
    void startUpsocket();
    bool getip();

    ~TcpClient();
};

