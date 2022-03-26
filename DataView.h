#pragma once
#include "interface.h"
#include <memory>

class DataView : public IViewObserver, public std::enable_shared_from_this<DataView>
{
public:
    using model =  std::shared_ptr<class TcpClient>;
private:
   
    model _model;

    DataView() = default;
    void showAnalogPoint(uint8_t *data);
    void showDigitalPoint(uint8_t *data);
    void showDigitalConrol(uint8_t *data);
public:
    
    static std::shared_ptr<DataView> create(model mod)
    {
        auto ptr =  std::shared_ptr<DataView>(new DataView());
        ptr->setModel(mod);
        return ptr;
    }

    std::shared_ptr<DataView> getptr();

    void setModel(model& model);

    void update(const std::string& message, const Frame* frame = nullptr) override;

    ~DataView() = default;

};
