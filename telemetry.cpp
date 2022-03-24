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
    start._length = HEADSIZE;
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

void Telemetry::stop()
{
    Frame start;
    start._frame_type = static_cast<decltype(start._frame_type)>(TypeFrame::Stop);
    start._length = HEADSIZE;
    start._payload = nullptr;
    
    if(_model->sendFrame(&start))
    {
        _model->notify("Sending STOP > ", &start);
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

void Telemetry::generalInterrogation()
{
    Frame start;
    start._frame_type = static_cast<decltype(start._frame_type)>(TypeFrame::GeneralInterrogation);
    start._length = HEADSIZE;
    start._payload = nullptr;
    
    if(_model->sendFrame(&start))
    {
        _model->notify("Sending GI > ", &start);
    }

    if(const auto& [ok, frame] = _model->recvAnswer(HEADSIZE); ok)
    {
        _model->notify("Receiving ACK < ", frame.get());
    }
    else
    {
        _model->notify("Error recv data");
    }
    if(const auto& [ok, frame] = _model->recvAnswer(HEADSIZE); ok)
    {
        _model->notify("Receiving DigitalPoints < ", frame.get());
    }
    else
    {
        _model->notify("Error recv data");
    }
    if(const auto& [ok, frame] = _model->recvAnswer(HEADSIZE); ok)
    {
        _model->notify("Receiving AnalogPoints < ", frame.get());
    }
    else
    {
        _model->notify("Error recv data");
    }
}

void Telemetry::digitalControl(uint32_t id, uint8_t val)
{
    Frame start;
    start._frame_type = static_cast<decltype(start._frame_type)>(TypeFrame::DigitalControl);
    start._length = 10;
    start._payload = std::make_unique<uint8_t[]>(5);
    
    start._payload[0] = static_cast<uint8_t>(2);
    start._payload[1] = static_cast<uint8_t>(0);
    start._payload[2] = static_cast<uint8_t>(0);
    start._payload[3] = static_cast<uint8_t>(0);
    start._payload[4] = val;
 
    if(_model->sendFrame(&start))
    {
        _model->notify("Sending DIGITAL_CONTROL > ", &start);

    }

    if(const auto& [ok, frame] = _model->recvAnswer(HEADSIZE); ok)
    {
        if(frame->_frame_type == static_cast<uint8_t>(TypeFrame::Nack))
        {
            _model->notify("Receiving Nack < ", frame.get());
            return;
        }
        _model->notify("Receiving ACK < ", frame.get());
    }
    else
    {
        _model->notify("Error recv data");
    }
    if(const auto& [ok, frame] = _model->recvAnswer(HEADSIZE); ok)
    {
        _model->notify("Receiving DigitalPoints < ", frame.get());
    }
    else
    {
        _model->notify("Error recv data");
    }
}
