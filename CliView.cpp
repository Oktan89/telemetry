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

void CliView::update(const std::string& message, const Frame& frame)
{
    std::cout << message;

    if(frame.getFrameType() != TypeFrame::Empty)
    {
        frame.printFrame();
    }
}