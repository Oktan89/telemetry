#include <iostream>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <memory>
#include <ctime>
#include "client.h"
#include "CliView.h"
#include "telemetry.h"
#include "type_traits_frame.h"
#include "interface.h"



int main(int argc, char* argv[])
{
    auto client = std::make_shared<TcpClient>("cpptest.08z.ru", 12567);
    auto cli = CliView::create(client);
    Telemetry telemetry(client);

    telemetry.start();
    telemetry.stop();


    return 0; 
}