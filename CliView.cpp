#include "CliView.h"
#include "client.h"
#include <string>
#include <iostream>
#include "type_traits_frame.h"


std::shared_ptr<CliView> CliView::getptr()
{
    return shared_from_this();
}

void CliView::setModel(model &model)
{
    if (_model)
        _model->removeObserver(shared_from_this());
    _model = model;
    _model->addObserver(shared_from_this());
}

void CliView::update(const std::string& message, const Frame* frame)
{
    std::cout << message;
    if(frame != nullptr)
    {
        if(frame->_frame_type != static_cast<decltype(frame->_frame_type)>(TypeFrame::Empty))
        {
            LENB l;
            l.leng.ln_in_int.len = frame->_length;

            std::cout<< std::hex <<std::setfill('0') 
                << std::setw(2) << (uint32_t) l.leng.ln_un_b.byte1 << " "
                << std::setw(2) << (uint32_t) l.leng.ln_un_b.byte2 << " "
                << std::setw(2) << (uint32_t) l.leng.ln_un_b.byte3 << " "
                << std::setw(2) << (uint32_t) l.leng.ln_un_b.byte4 << " "
                << std::setw(2) << (uint32_t)frame->_frame_type << " ";
        }
        if(frame->_payload)
        {
            for(std::size_t i = 0; i < frame->_length - HEADSIZE; ++i)
            {
                std::cout << std::hex << std::setfill('0')
                    << std::setw(2) << (uint32_t)frame->_payload[i] << " ";
            }
        }
    }
    std::cout << std::endl;
}

//std::cout<<std::resetiosflags(std::ios_base::basefield)<<std::endl;