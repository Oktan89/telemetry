#pragma once
// #include "interface.h"
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



    using uint32_lsb_t = uint32_t;

    uint32_t swap_uint32(uint32_t in);


    uint32_lsb_t uint32_to_lsb(uint32_t in);


    uint32_t lsb_to_uint32(uint32_lsb_t in);

// Качество Quality – беззнаковое целое 1 байт:
// 1.	Значение достоверно Valid – 1 бит
// 2.	Значение установлено вручную Substituted – 2 бит
// 3.	Значение переполнено Overflow – 3 бит
struct Quality
{
    uint8_t value;
};

// Дискретный сигнал DigitalPoint:
// 1.	Номер сигнала PointId – беззнаковое целое 4 байта LSB
// 2.	Значение сигнала Value – беззнаковое целое 1 байт
// 3.	Метка времени (unix-time) TimeTag – целое 8 байт LSB
// 4.	Качество сигнала Quality тип данных Quality

struct DigetalPoint
{
    uint32_t point_id;
    uint8_t value;
    uint64_t time_tag;
    Quality quality;
};
// Аналоговый сигнал AnalogPoint:
// 1.	Номер сигнала PointId – беззнаковое целое 4 байта LSB
// 2.	Значение сигнала Value – число с плавающей точкой 4 байт LSB
// 3.	Метка времени (unix-time) TimeTag – целое 8 байт LSB
// 4.	Качество сигнала Quality тип данных Quality

struct AnalogPoint
{
    uint32_t point_id;
    float value;
    uint64_t time_tag;
    Quality quality;
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

// Номер сигнала PointId – беззнаковое целое 4 байта LSB
// Значение сигнала Value – беззнаковое целое 1 байт
struct DigitalControl
{
    uint32_t  point_id;
    uint8_t value;
};

struct Frame 
{
    uint32_t _length{0};
    uint8_t _frame_type{0};
    std::unique_ptr<uint8_t[]> _payload;
    // void *_payload{nullptr};
};




