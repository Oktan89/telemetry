#include "DataView.h"
#include "client.h"
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <memory>
#include <ctime>
#include "type_traits_frame.h"



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
            showAnalogPoint(frame->_payload.get());
            break;
        case TypeFrame::DigitalPoints :
            showDigitalPoint(frame->_payload.get());
            break;
        case TypeFrame::DigitalControl :
            showDigitalConrol(frame->_payload.get());
            break;
        }
    }

}

void DataView::showAnalogPoint(uint8_t *data)
{
    auto head = std::make_unique<headPoint>();
    memcpy(head.get(), data, sizeof(headPoint));

    auto point = std::make_unique<AnalogPoint[]>(head->count);
    data = data + sizeof(headPoint);
    memcpy(point.get(), data, sizeof(AnalogPoint)*head->count);
    std::cout << std::endl;
    convert_LSB_MSB(point, head->count);
    
    for(std::size_t i = 0; i < head->count; ++i)
    {   
        std::time_t time = point[i].time_tag;
        std::cout << "\tPointId= " << point[i].point_id << ", Value= " 
            << std::setprecision(1) << std::fixed << static_cast<float>(point[i].value) 
            << ", TimeTag = " << std::put_time(std::localtime(&time), "%d.%m.%Y %T") 
            <<", Quality = [" << point[i].quality.getQuality() << "]" 
            << std::endl;
    }
}

void DataView::showDigitalConrol(uint8_t *data)
{
    auto frameConrol = std::make_unique<DigitalControl>();
    memcpy(frameConrol.get(), data, sizeof(DigitalControl));
    std::cout << std::endl;
    std::cout << "\tPointId = " << frameConrol->point_id 
        << ", Value = "<< static_cast<uint32_t>(frameConrol->value) 
        << std::endl;
}

void DataView::showDigitalPoint(uint8_t *data)
{   
    auto head = std::make_unique<headPoint>();
    memcpy(head.get(), data, sizeof(headPoint));

    auto point = std::make_unique<DigetalPoint[]>(head->count);
    data = data + sizeof(headPoint);
    memcpy(point.get(), data, sizeof(DigetalPoint)*head->count);
    std::cout << std::endl;
    convert_LSB_MSB(point, head->count);

    for(std::size_t i = 0; i < head->count; ++i)
    {
        std::time_t time = point[i].time_tag;
        std::cout << "\tPointId= " << point[i].point_id << ", Value= " 
            << static_cast<uint32_t>(point[i].value) 
            << ", TimeTag = " << std::put_time(std::localtime(&time), "%d.%m.%Y %T") 
            <<", Quality = [" << point[i].quality.getQuality() << "]" 
            << std::endl;
    }
}

void DataView::setLSB()
{
    isLBS = true;
}

void DataView::setMSB()
{
    isLBS = false;
}

std::string DataView::checkEndian()
{
     uint16_t x = 0x0001;
     *((uint8_t *) &x) ? setLSB() : setMSB();
     return (isLBS)? "Set Little-endian" : "Set Big-endian";
}

DataView::DataView()
{
    std::cout << checkEndian() << std::endl;
}