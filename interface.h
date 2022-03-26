#pragma once
#include <string>
#include "type_traits_frame.h"
#include <memory>

struct IViewObserver
{
    virtual void update(const std::string&, const Frame* frame = nullptr) = 0;
    ~IViewObserver() = default;
};

struct IModelObservable
{
    virtual void addObserver(std::shared_ptr<IViewObserver>) = 0;
    virtual void removeObserver(std::shared_ptr<IViewObserver>) = 0;
    virtual void notify(const std::string&, const Frame* frame = nullptr) const = 0;
    ~IModelObservable() = default;
};
