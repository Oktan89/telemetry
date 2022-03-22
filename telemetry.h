#pragma once
#include <memory>
#include "interface.h"

class TcpClient;

class Telemetry
{
    
    std::shared_ptr<TcpClient> _model;

public:
    explicit Telemetry(std::shared_ptr<TcpClient> model) : _model(model){}

    // void setModelState();
    
    int start();
};