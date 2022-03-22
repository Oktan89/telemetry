#include "CliView.h"
#include "client.h"
#include <string>
#include <iostream>


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

void CliView::update(const std::string& message)
{
    std::cout << message << std::endl;
}