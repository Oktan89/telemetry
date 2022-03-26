#pragma once
#include "interface.h"
#include <memory>

class ProtocolView : public IViewObserver, public std::enable_shared_from_this<ProtocolView>
{
public:
    using model =  std::shared_ptr<class TcpClient>;
private:
   
    model _model;

    ProtocolView() = default;
public:
    
    static std::shared_ptr<ProtocolView> create(model mod)
    {
        auto ptr =  std::shared_ptr<ProtocolView>(new ProtocolView());
        ptr->setModel(mod);
        return ptr;
    }

    std::shared_ptr<ProtocolView> getptr();

    void setModel(model& model);

    void update(const std::string& message, const Frame* frame = nullptr) override;

    ~ProtocolView() = default;

};

