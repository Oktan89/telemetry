#pragma once
#include "interface.h"
#include <memory>

class DataView : public IViewObserver, public std::enable_shared_from_this<DataView>
{
public:
    using model =  std::shared_ptr<class TcpClient>;
private:
   
    model _model;

    bool isLBS{true};

    DataView();
    void showAnalogPoint(uint8_t *data);
    void showDigitalPoint(uint8_t *data);
    void showDigitalConrol(uint8_t *data);
    template<typename T>
    void convert_LSB_MSB(T &point, uint16_t size)
    {
        if(!isLBS)
            for(std::size_t i = 0; i < size; ++i)
            {
                point[i].point_id = lsb_to_uint32(point[i].point_id);
                point[i].value = lsb_to_uint32(point[i].value);
                point[i].time_tag = lsb_to_uint32(point[i].time_tag);
            }
    }
public:
    
    static std::shared_ptr<DataView> create(model mod)
    {
        auto ptr =  std::shared_ptr<DataView>(new DataView());
        ptr->setModel(mod);
        return ptr;
    }

    std::shared_ptr<DataView> getptr();

    void setModel(model& model);

    void setLSB();

    void setMSB();

    std::string checkEndian();

    void update(const std::string& message, const Frame* frame = nullptr) override;

    ~DataView() = default;

};
