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
            std::cout<< std::hex <<std::setfill('0') << std::setw(2) << frame->_length <<" "<< (int)frame->_frame_type <<"\n";
            //std::cout<<std::resetiosflags(std::ios_base::basefield)<<std::endl;
        }
    }
 
}

