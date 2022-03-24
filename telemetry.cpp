#include "telemetry.h"
#include "client.h"
#include "type_traits_frame.h"

constexpr int HEADSIZE =  5;

Telemetry::Telemetry(std::shared_ptr<TcpClient> model): _model(model)
{
    _model->startUpsocket();
    _model->getip();
    _model->StartConnect();
}

void Telemetry::start()
{
    Frame start;
    start._frame_type = static_cast<decltype(start._frame_type)>(TypeFrame::Start);
    start._length = 5;
    start._payload = nullptr;
    
    if(_model->sendFrame(&start))
    {
        _model->notify("Sending START > ", &start);
    }

    if(const auto& [ok, frame] = _model->recvAnswer(HEADSIZE); ok)
    {
        _model->notify("Receiving ACK < ", frame.get());
    }
    else
    {
        _model->notify("Error recv data");
    }
}


// void Telemetry::setModelState()
// {
//     std::unique_ptr<__BaseState> state_static = std::make_unique<StaticBlock>();
//     _model->TransitionTo(state_static);
// }