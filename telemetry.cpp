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
    start.setFrameType(TypeFrame::Start);
    if(_model->sendFrame(start))
    {
        _model->notify("Sending START > ", start);
    }

    if(const auto& [ok, frame] = _model->recvAnswer(HEADSIZE); ok)
    {
        switch(frame->getFrameType())
        {
            case TypeFrame::Ack:
                _model->notify("Receiving ACK < ", *frame->getDataFrame());
            break;

            case TypeFrame::Nack:
                _model->notify("Receiving Nack < ", *frame->getDataFrame());
            break;

            default:
                _model->notify("Receiving Frame Type Error ! ["+
                    std::to_string(static_cast<int>(frame->getFrameType())) +"]\n");
        }
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

    if(const auto& [ok, frame] = _model->recvAnswer(HEADSIZE); ok)
    {
        switch(frame->getFrameType())
        {
            case TypeFrame::Ack:
                _model->notify("Receiving ACK < ", *frame->getDataFrame());
            break;

            case TypeFrame::Nack:
                _model->notify("Receiving Nack < ", *frame->getDataFrame());
            break;

            default:
                _model->notify("Receiving Frame Type Error ! ["+
                    std::to_string(static_cast<int>(frame->getFrameType())) +"]\n");
        }
        
    }
    else
    {
        _model->notify("Error recv data");
    }
}

void Telemetry::generalInterrogation()
{
    Frame gi;
    gi.setPayLoad(std::make_unique<DigetalPoint>());
    gi.setFrameType(TypeFrame::GeneralInterrogation);
    

    if(_model->sendFrame(gi))
    {
        _model->notify("Sending GI > ", gi);
    }

    if(const auto& [ok, frame] = _model->recvAnswer(HEADSIZE); ok)
    {
        switch(frame->getFrameType())
        {
            case TypeFrame::Ack:
                _model->notify("Receiving ACK < ", *frame->getDataFrame());
                
                if(const auto& [ok, frame] = _model->recvAnswer(HEADSIZE); ok)
                {
                    _model->notify("Digital < ", *frame->getDataFrame());
                }
            break;

            case TypeFrame::Nack:
                _model->notify("Receiving Nack < ", *frame->getDataFrame());
            break;

            default:
                _model->notify("Receiving Frame Type Error ! ["+
                    std::to_string(static_cast<int>(frame->getFrameType())) +"]\n");
        }
        
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