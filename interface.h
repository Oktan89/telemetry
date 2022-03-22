#pragma once
#include <memory>
#include <string>

struct IViewObserver
{
    virtual void update(const std::string&) = 0;
    ~IViewObserver() = default;
};

struct IModelObservable
{
    virtual void addObserver(std::shared_ptr<IViewObserver>) = 0;
    virtual void removeObserver(std::shared_ptr<IViewObserver>) = 0;
    virtual void notify(const std::string&) = 0;
    ~IModelObservable() = default;
};
