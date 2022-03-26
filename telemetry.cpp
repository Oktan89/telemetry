#include "telemetry.h"
#include "client.h"
#include "type_traits_frame.h"

std::unique_ptr<uint8_t[]> setDigitalSygnal(uint32_t id, uint8_t val)
{
    DSYGNAl number;
    number.point_id.id_un_int.val_id = 2;
    auto payload = std::make_unique<uint8_t[]>(5);

        payload[0] = number.point_id.id_un_b.byte1;
        payload[1] = number.point_id.id_un_b.byte2;
        payload[2] = number.point_id.id_un_b.byte3;
        payload[3] = number.point_id.id_un_b.byte4;
        payload[4] = val;
    return payload;
}

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

    if(const auto& [ok, frame] = _model->recvAnswer(); ok)
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

    if(const auto& [ok, frame] = _model->recvAnswer(); ok)
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

    if(const auto& [ok, frame] = _model->recvAnswer(); ok)
    {
        _model->notify("Receiving ACK < ", frame.get());
    }
    else
    {
        _model->notify("Error recv data");
    }
    if(const auto& [ok, frame] = _model->recvAnswer(); ok)
    {
        _model->notify("Receiving DigitalPoints < ", frame.get());
    }
    else
    {
        _model->notify("Error recv data");
    }
    if(const auto& [ok, frame] = _model->recvAnswer(); ok)
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
    start._payload = setDigitalSygnal(id, val);
    
 
    if(_model->sendFrame(&start))
    {
        _model->notify("Sending DIGITAL_CONTROL > ", &start);

    }

    if(const auto& [ok, frame] = _model->recvAnswer(); ok)
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
    if(const auto& [ok, frame] = _model->recvAnswer(); ok)
    {
        _model->notify("Receiving DigitalPoints < ", frame.get());
    }
    else
    {
        _model->notify("Error recv data");
    }
}
