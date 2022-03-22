#include <iostream>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <memory>
#include "client.h"
#include "CliView.h"
#include "telemetry.h"
#include "type_traits_frame.h"


int main(int argc, char* argv[])
{
    auto client = std::make_shared<TcpClient>("cpptest.08z.ru", 12567);
    auto cli = CliView::create(client);
    Telemetry telemetry(client);

    telemetry.start();

    // Frame test;
    // test.setFrameType(TypeFrame::Start);
    // test.printFrame();
    return 0; 
}