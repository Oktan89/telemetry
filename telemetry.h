#pragma once
#include <memory>
#include "interface.h"

class TcpClient;

class Telemetry
{
    
    std::shared_ptr<TcpClient> _model;

public:
    explicit Telemetry(std::shared_ptr<TcpClient> model);

    void start();

    void stop();

    void generalInterrogation();

    void digitalControl(uint32_t id, uint8_t val);
};