#pragma once
#include <vector>
#include <cassert>
#include <iomanip>
#include <iostream>

enum class TypeFrame
{
    Empty = 0,
    DigitalPoints = 1,
    AnalogPoints = 2,
    DigitalControl = 3,
    Start = 4,
    Stop = 5,
    GeneralInterrogation = 6,
    Ack = 7,
    Nack = 8
};

class Frame
{
    std::vector<char> m_frame;
    union size_f
    {
        unsigned long number;
        unsigned char byte[sizeof(unsigned long)];
    };
    
public:
    Frame()
    {
        m_frame.reserve(5);
        m_frame = { 0, 0, 0, 0, 0};
    }

    const char* getDataFrame() const
    {
        return m_frame.data();
    }

    std::size_t size() const noexcept
    {
        return m_frame.size();
    }

    void setFrameBuf(const char* buf, std::size_t size)
    {
        if(m_frame.empty())
        {
            m_frame.reserve(size);
        }
        for(std::size_t i = 0; i < size; ++i)
        {
            m_frame[i] = buf[i];
        }
    }

    void setFrameType(TypeFrame type)
    {
        m_frame[4] = static_cast<char> (type);
        updateLength();
    }

    void printFrame() const
    {
        std::size_t size = m_frame.size();
        for(std::size_t i = 0; i < size; ++i)
        {
            std::cout<< std::hex <<std::setfill('0') << std::setw(2) << static_cast<int>(m_frame[i])<< " ";
        }
        std::cout<<std::resetiosflags(std::ios_base::basefield)<<std::endl;
    }

private:
    void updateLength() noexcept
    {
        size_f s;
        s.number = m_frame.size();
        for(std::size_t i = 0; i < s.number; ++i)
            m_frame[i] = s.byte[i];
    }

    

};