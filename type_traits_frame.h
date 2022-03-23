#pragma once
#include "interface.h"
#include <vector>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <memory>


enum class TypeFrame
{
    Empty                   = 0,
    DigitalPoints           = 1,
    AnalogPoints            = 2,
    DigitalControl          = 3,
    Start                   = 4,
    Stop                    = 5,
    GeneralInterrogation    = 6,
    Ack                     = 7,
    Nack                    = 8
};

// Причина передачи TransmissionType:
// •	Общий опрос Interrogation = 1
// •	Спорадическая передача Spontaneous = 2

enum class TransmissionType
{
    Interrogation = 1,
    Spontaneous = 2
};

// Качество Quality – беззнаковое целое 1 байт:
// 1.	Значение достоверно Valid – 1 бит
// 2.	Значение установлено вручную Substituted – 2 бит
// 3.	Значение переполнено Overflow – 3 бит
struct Quality
{
    uint8_t value;
};

struct __base_pay_load
{
    using uint32_lsb_t = uint32_t;

    uint32_t point_id;
    uint8_t value;
    uint64_t time_tag;
    Quality quality;

    uint32_t swap_uint32(uint32_t in)
    {
        uint32_t swapped = ((in >> 24) & 0xff) |
                ((in << 8) & 0xff0000) |
                ((in >> 8) & 0xff00) |
                ((in << 24) & 0xff000000);
        return(swapped);
    }

    uint32_lsb_t uint32_to_lsb(uint32_t in) 
    {
        return((uint32_lsb_t)swap_uint32(in));
    }

    uint32_t lsb_to_uint32(uint32_lsb_t in) {
        return(swap_uint32((uint32_t)in));
    }
};

// Дискретный сигнал DigitalPoint:
// 1.	Номер сигнала PointId – беззнаковое целое 4 байта LSB
// 2.	Значение сигнала Value – беззнаковое целое 1 байт
// 3.	Метка времени (unix-time) TimeTag – целое 8 байт LSB
// 4.	Качество сигнала Quality тип данных Quality

class DigetalPoint : public __base_pay_load
{
public:

};
// Аналоговый сигнал AnalogPoint:
// 1.	Номер сигнала PointId – беззнаковое целое 4 байта LSB
// 2.	Значение сигнала Value – число с плавающей точкой 4 байт LSB
// 3.	Метка времени (unix-time) TimeTag – целое 8 байт LSB
// 4.	Качество сигнала Quality тип данных Quality

class AnalogPoint : public __base_pay_load
{
    float value;
public:

};

// Формат кадра:
// 1.	Длина всего кадра Length – беззнаковое целое 4 байта LSB
// 2.	Тип кадра FrameType – беззнаковое целое 1 байт
// a.	DigitalPoints = 1
//      AnalogPoints = 2
//      DigitalControl = 3
//      Start = 4
//      Stop = 5
//      GeneralInterrogation = 6
//      Ack = 7
//      Nack = 8
// 3.	Полезная нагрузка Payload
class Frame 
{
    uint32_t _length;
    uint8_t _frame_type;
    std::unique_ptr<__base_pay_load> uniq_payload;
    mutable std::vector<char> frame;
public:
    Frame() : _length(4), _frame_type(0), uniq_payload(nullptr){}

    ~Frame() = default;

    void setPayLoad(std::unique_ptr<__base_pay_load>&& payload) noexcept
    {
        uniq_payload.swap(payload);
    }

    std::size_t size() const noexcept
    {
        return _length;
    }

    const Frame* getDataFrame() const noexcept
    {
        
        const uint32_t *lptr = &_length;
        const char* ptr = reinterpret_cast<char*>(const_cast<uint32_t*>(lptr));
        for(std::size_t i = 0; i < _length; ++i)
        {
            frame.push_back(*ptr);
            ++ptr;
        }

        return this;
    }

    void setFrameType(TypeFrame type) noexcept
    {
        ++_length;
        _frame_type = static_cast<uint8_t>(type);
    }

    TypeFrame getFrameType() const noexcept
    {
        return static_cast<TypeFrame>(_frame_type);
    }

    void printFrame() const
    {
        for(std::size_t i = 0; i < _length; ++i)
        {
            std::cout<< std::hex <<std::setfill('0') << std::setw(2) << static_cast<int>(frame[i])<< " ";
        }
        std::cout<<std::resetiosflags(std::ios_base::basefield)<<std::endl;
    }
};





// printf("uint32_lsb_to(5):%d\n",uint32_to_lsb(5));