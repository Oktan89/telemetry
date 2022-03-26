#include <iostream>
#include <vector>
#include <memory>
#include <ctime>
#include "client.h"
#include "ProtocolView.h"
#include "DataView.h"
#include "telemetry.h"
#include "type_traits_frame.h"
#include "interface.h"



int main(int argc, char* argv[])
{
    auto client = std::make_shared<TcpClient>("cpptest.08z.ru", 12567);
    auto cli = ProtocolView::create(client);
    auto data = DataView::create(client);
    Telemetry telemetry(client);
    
    telemetry.start();
    telemetry.generalInterrogation();
    telemetry.digitalControl(2, 1);
    telemetry.stop();

    return 0; 
}
