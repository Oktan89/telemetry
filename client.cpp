#include "client.h"
#include <algorithm>
#include <stdexcept>

void TcpClient::addObserver(std::shared_ptr<IViewObserver> observer) 
{
    __observer.emplace_back(observer);
}

void TcpClient::removeObserver(std::shared_ptr<IViewObserver> observer)
{
    auto it = std::find_if(__observer.cbegin(), __observer.cend(), [&](const std::weak_ptr<IViewObserver>& sub){
            auto itr = sub.lock();
            return itr == observer;
        });
        if(it != __observer.end())
            __observer.erase(it);
}

void TcpClient::notify(const std::string& message)
{
    for(auto it = __observer.begin(); it != __observer.end(); ++it)
    {
        auto ptr = it->lock();
        if(ptr)
            ptr->update(message);
        else
            __observer.erase(it++);
    }    
}

TcpClient::TcpClient(const std::string& serveraddr, u_short port) :
m_servername(serveraddr), m_port(port)
{
    ZeroMemory(&m_servInfo, sizeof(m_servInfo));
    m_servInfo.sin_family = AF_INET;
    m_servInfo.sin_port = htons(m_port);
}

void TcpClient::startUpsocket()
{
    if(WSAStartup(MAKEWORD(2,2), &ws_data))
    {
        throw std::runtime_error("Error WinSock version initializaion #" +
		std::to_string(WSAGetLastError()));
    }
    else
    {
        notify("WinSock initialization is OK");
    }

    m_soket = socket(AF_INET, SOCK_STREAM, 0);

	if (m_soket == INVALID_SOCKET) {
		throw std::runtime_error("Error initialization socket # " +
        std::to_string(WSAGetLastError()));
	}
	else
		notify("Server socket initialization is OK");
}

bool TcpClient::getip()
{
    if (inet_addr(m_servername.c_str()) != INADDR_NONE)
        m_servInfo.sin_addr.s_addr = inet_addr(m_servername.c_str());
    else
    {
        // попытка получить IP адрес по доменному имени сервера
        if (hst = gethostbyname(m_servername.c_str()))
            // hst->h_addr_list содержит не массив адресов,
            // а массив указателей на адреса
            ((unsigned long *)&m_servInfo.sin_addr)[0] =
            ((unsigned long **)hst->h_addr_list)[0][0];
        else
        {
            notify("Invalid address " + m_servername);
            return false;
        }
    }
    return true;
}

bool TcpClient::StartConnect()
{
    
    if (connect(m_soket, (sockaddr*)&m_servInfo, sizeof(m_servInfo))) 
    {
		notify("Connection to Server is FAILED. Error # " +
        std::to_string(WSAGetLastError()));
        return false;
	}
	else 
		notify("Connection established SUCCESSFULLY");  
    return true;
}

TcpClient::~TcpClient()
{
    closesocket(m_soket);
	WSACleanup();
}