#include "telemetry.h"
#include "client.h"

int Telemetry::start()
{
    _model->startUpsocket();
    _model->getip();
    _model->StartConnect();
      
    
    return 0;
}

// void Telemetry::setModelState()
// {
//     std::unique_ptr<__BaseState> state_static = std::make_unique<StaticBlock>();
//     _model->TransitionTo(state_static);
// }