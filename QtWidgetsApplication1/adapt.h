#pragma once

#include <string>
#include <map>
#include <typeinfo>

typedef std::pair<const std::string, const std::type_info*> mapkey;

extern std::map<mapkey, void*> adapters;

template<typename AdapteeType, typename Interface> struct Adapter: Interface {
    
    typedef AdapteeType Adaptee;
    typedef Interface Interface;

    AdapteeType* adaptee = nullptr;

    void setAdaptee(AdapteeType* obj) {
        adaptee = obj;
    };

};


template<typename AdapterType> void register_adapter() {
    mapkey key = std::make_pair(AdapterType::Adaptee::data_type_id, &typeid(AdapterType::Interface));
    void* adapter = new AdapterType();
    adapters.emplace(key, adapter);
};


template<typename Interface, typename Adaptee> Interface* adapt(Adaptee* obj) {
    auto ti_interface = &typeid(Interface);
    auto ti_adaptee = obj->get_data_type_id();
    const auto key = std::make_pair(ti_adaptee, ti_interface);
    if (adapters.count(key) == 0) return nullptr;
    auto* adapter = static_cast<Adapter<Adaptee, Interface>*>(adapters[key]);
    adapter->setAdaptee(obj);
    return adapter;
}


