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

// class TcpClient;
// class __BaseState
// {
// protected:
//     std::shared_ptr<TcpClient> _modelContext;

// public:
    
//     void setModelContext(std::shared_ptr<TcpClient> model)
//     {   
//         _modelContext = model;
//     }
//     virtual void ReadBlock() = 0;
//     virtual void EndBlock() = 0;
//     virtual void StartBlock() = 0;
//     virtual void Exit() = 0;
//     ~__BaseState() = default;
// };