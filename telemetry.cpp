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
        _model->notify("Sending START > ", start);
    }

    if(const auto& [ok, frame] = _model->recvAnswer(5); ok)
    {
        _model->notify("Receiving ACK < ", *frame->getDataFrame());
    }
    else
    {
        _model->notify("Error recv data");
    }
}

void Telemetry::stop()
{
    Frame stop;
    stop.setFrameType(TypeFrame::Stop);

    if(_model->sendFrame(stop))
    {
        _model->notify("Sending STOP > ", stop);
    }

    if(const auto& [ok, frame] = _model->recvAnswer(5); ok)
    {
        _model->notify("Receiving ACK < ", *frame->getDataFrame());
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