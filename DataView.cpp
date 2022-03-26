#include "DataView.h"
#include "client.h"
#include <string>
#include <vector>
#include <iostream>
#include "type_traits_frame.h"

void showAnalogPoint(const uint8_t *data, std::size_t size);
void showDigitalPoint(uint8_t *data, std::size_t size);

std::shared_ptr<DataView> DataView::getptr()
{
    return shared_from_this();
}

void DataView::setModel(model &model)
{
    if (_model)
        _model->removeObserver(shared_from_this());
    _model = model;
    _model->addObserver(shared_from_this());
}

void DataView::update(const std::string& message, const Frame* frame)
{
    if(frame && frame->_payload)
    {
        std::cout<< "[Data] " + message;
        switch (static_cast<TypeFrame>(frame->_frame_type))
        {
        case TypeFrame::AnalogPoints :
            showAnalogPoint(frame->_payload.get(), frame->_length);
            break;
        case TypeFrame::DigitalPoints :
            showDigitalPoint(frame->_payload.get(), frame->_length);
            break;
        case TypeFrame::DigitalControl :
            std::cout << "digitalcontrol" << std::endl;
        default:
            break;
        }
    }

}

void showAnalogPoint(const uint8_t *data, std::size_t size)
{
    std::cout << "Analog point frame size " << size;
    std::cout << std::endl;
}

void showDigitalPoint(uint8_t *data, std::size_t size)
{   //  Размер кадра LSB  Type   Причина   Col LSB      LSB ID          value               time LSB              качество
    // [32][00][00][00] | [01] |  [01]   | [03][00] | [01][00][00][00]|  [01] | [ab][ab][3e][62][00][00][00][00] | [01] ...
    //   0  1    2   3      4       5       6   7       8  9   10  11     12     13  14  15  16  17  18  19  20     21 
    // DigetalPoint point;
    
    // // uint8_t *id = data;
    // //id = id+5;
    // uint32_t *idt = reinterpret_cast<uint32_t*>(data);
    // std::cout << "Колличество ID " << lsb_to_uint32(*idt) << std::endl;
    std::cout << "test" << 
}