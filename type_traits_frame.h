#pragma once

#include <vector>
#include <iomanip>
#include <iostream>
#include <memory>
#include <bitset>
#include <cstdint>

constexpr int HEADSIZE =  5;

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
    std::string getQuality()
    {
        std::bitset<8> q(value);
        std::string quality;
        quality = "Invalid";
        if(q.any())
        {
            if(q.test(0)) quality = "Valid";
            if(q.test(1)) quality += ", Substituted";
            if(q.test(2)) quality += ", Overflow";
        }
                
        return quality;
    }
};

// ◦ Причина передачи CauseOfTransmission – 1 байт
// ◦ Количество сигналов Count – беззнаковое целое 2 байта LSB

#ifdef _MSC_VER
#pragma pack (push, 1)
struct   headDigital
#endif
#ifndef _MSC_VER 
struct __attribute__((__packed__)) headPoint
#endif 
{
    uint8_t reason;
    uint16_t count;
};
#ifdef _MSC_VER
#pragma pack (pop)
#endif
// Дискретный сигнал DigitalPoint:
// 1.	Номер сигнала PointId – беззнаковое целое 4 байта LSB
// 2.	Значение сигнала Value – беззнаковое целое 1 байт
// 3.	Метка времени (unix-time) TimeTag – целое 8 байт LSB
// 4.	Качество сигнала Quality тип данных Quality

#ifdef _MSC_VER
#pragma pack (push, 1)
struct   DigetalPoint
#endif
#ifndef _MSC_VER 
struct __attribute__((__packed__)) DigetalPoint
#endif 
{
    uint32_t point_id;
    uint8_t value;
    int64_t time_tag;
    Quality quality;
};
#ifdef _MSC_VER
#pragma pack (pop)
#endif

// Аналоговый сигнал AnalogPoint:
// 1.	Номер сигнала PointId – беззнаковое целое 4 байта LSB
// 2.	Значение сигнала Value – число с плавающей точкой 4 байт LSB
// 3.	Метка времени (unix-time) TimeTag – целое 8 байт LSB
// 4.	Качество сигнала Quality тип данных Quality
#ifdef _MSC_VER
#pragma pack (push, 1)
struct   DigetalPoint
#endif
#ifndef _MSC_VER 
struct __attribute__((__packed__)) AnalogPoint
#endif 
{
    uint32_t point_id;
    float value;
    uint64_t time_tag;
    Quality quality;
};
#ifdef _MSC_VER
#pragma pack (pop)
#endif


// Номер сигнала PointId – беззнаковое целое 4 байта LSB
// Значение сигнала Value – беззнаковое целое 1 байт
struct DigitalControl
{
    uint32_t  point_id;
    uint8_t value;
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

struct Frame 
{
    uint32_t _length;
    uint8_t _frame_type;
    std::unique_ptr<uint8_t[]> _payload;
};

typedef struct Length
{
    union 
    {
       struct 
       {
           uint8_t byte1, byte2, byte3, byte4;
       } ln_un_b;
       struct 
       {
           uint32_t len;
       } ln_in_int;
       
    }leng;
} LENB;


// • Значение полезной нагрузки Payload DigitalControl:
//     ◦ Номер сигнала PointId – беззнаковое целое 4 байта LSB
//     • Значение полезной нагрузки Payload:
//     ◦ Значение сигнала Value – беззнаковое целое 1 байт
typedef struct SygnalPointId
{
    union
    {
        struct
        {
            uint8_t byte1, byte2, byte3, byte4;
        } id_un_b;
        struct
        {
            uint32_t val_id;
        } id_un_int;
    } point_id;
} DSYGNAl;

using uint32_lsb_t = uint32_t;

uint32_t swap_uint32(uint32_t in);


uint32_lsb_t uint32_to_lsb(uint32_t in);


uint32_t lsb_to_uint32(uint32_lsb_t in);

template <typename T>
void SwapEndiannes(T& var)
{
    char* varArray = reinterpret_cast<char*>(&var);

    for(std::size_t i = 0; i < static_cast<std::size_t>(sizeof(var)/2); ++i)
    {
        std::swap(varArray[sizeof(var) -1 - i], varArray[i]);
    }
}