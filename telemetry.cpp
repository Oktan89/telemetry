#include "telemetry.h"
#include "client.h"
#include "type_traits_frame.h"

Telemetry::Telemetry(std::shared_ptr<TcpClient> model): _model(model)
{
    _model->startUpsocket();
    _model->getip();
    _model->StartConnect();
}

void Telemetry::start()
{
    Frame start;
    start.setFrameType(TypeFrame::Start);
    if(_model->sendFrame(start))
    {
        _model->notify("Sending START");
    }

}

// void Telemetry::setModelState()
// {
//     std::unique_ptr<__BaseState> state_static = std::make_unique<StaticBlock>();
//     _model->TransitionTo(state_static);
// }