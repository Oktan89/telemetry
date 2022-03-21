#include <iostream>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>


#define PORT 12567
#define SERVERADDR "cpptest.08z.ru" //Звёздочками пометил свой IP
 
int main(int argc, char* argv[])
{
    WSADATA ws_data;

    int errStat = WSAStartup(MAKEWORD(2,2), &ws_data);

    if(errStat)
    {
        std::cout << "Error WinSock version initializaion #";
		std::cout << WSAGetLastError();
		return 1;
    }
    else
    {
        std::cout << "WinSock initialization is OK" << std::endl;
    }

    SOCKET clientSock = socket(AF_INET, SOCK_STREAM, 0);

	if (clientSock == INVALID_SOCKET) {
		std::cout << "Error initialization socket # " << WSAGetLastError() << std::endl; 
		closesocket(clientSock);
		WSACleanup();
		return 1;
	}
	else
		std::cout << "Server socket initialization is OK" << std::endl;

    sockaddr_in servInfo;
    ZeroMemory(&servInfo, sizeof(servInfo));	
				
    servInfo.sin_family = AF_INET;
    servInfo.sin_port = htons(PORT);
    HOSTENT *hst;
 
    // преобразование IP адреса из символьного в сетевой формат
    if (inet_addr(SERVERADDR) != INADDR_NONE)
        servInfo.sin_addr.s_addr = inet_addr(SERVERADDR);
    else
    {
        // попытка получить IP адрес по доменному имени сервера
        if (hst = gethostbyname(SERVERADDR))
            // hst->h_addr_list содержит не массив адресов,
            // а массив указателей на адреса
            ((unsigned long *)&servInfo.sin_addr)[0] =
            ((unsigned long **)hst->h_addr_list)[0][0];
        else
        {
            printf("Invalid address %s\n", SERVERADDR);
            closesocket(clientSock);
            WSACleanup();
            return -1;
        }
    }
 
    errStat = connect(clientSock, (sockaddr*)&servInfo, sizeof(servInfo));
    if ( errStat != 0 ) {
		std::cout << "Connection to Server is FAILED. Error # " << WSAGetLastError() << std::endl;
		closesocket(clientSock);
		WSACleanup();
		return 1;
	}
	else 
		std::cout << "Connection established SUCCESSFULLY. Ready to send a message to Server" << std::endl;  

    
   union 
   {
       unsigned char ss;
        struct {
        unsigned a:1;
        unsigned b:1;
        unsigned c:1;
        unsigned d:1;
        unsigned e:1;
        unsigned f:1;
        unsigned g:1;
        unsigned h:1;
        }bit;
   }cod;

    cod.ss = 5;
    std::cout << sizeof(cod) << std::endl;
    std::cout << cod.bit.h << cod.bit.g << cod.bit.g << cod.bit.f << cod.bit.e << cod.bit.d << cod.bit.c << cod.bit.b << cod.bit.a <<std::endl;
    closesocket(clientSock);
	WSACleanup();
}