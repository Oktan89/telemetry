#pragma once
#include <memory>
#include <string>
#include "type_traits_frame.h"

struct IViewObserver
{
    virtual void update(const std::string&, const Frame& frame = Frame()) = 0;
    ~IViewObserver() = default;
};

struct IModelObservable
{
    virtual void addObserver(std::shared_ptr<IViewObserver>) = 0;
    virtual void removeObserver(std::shared_ptr<IViewObserver>) = 0;
    virtual void notify(const std::string&, const Frame& frame = Frame()) const = 0;
    ~IModelObservable() = default;
};
