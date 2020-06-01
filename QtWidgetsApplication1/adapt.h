#pragma once

#include <string>
#include <map>
#include <typeinfo>

typedef std::pair<const std::string, const std::type_info*> mapkey;

extern std::map<mapkey, void*> adapters;

template<typename AdapteeType, typename Interface> struct Adapter : Interface {

    typedef AdapteeType Adaptee;
    typedef Interface Interface;

    static_assert(std::is_base_of<IAdaptable, Adaptee>::value, "Adaptee must derive from IAdaptable");

    AdapteeType* adaptee = nullptr;

    void setAdaptee(AdapteeType* obj) {
        adaptee = obj;
    }
};

// Introduce IBuild base class to force adapt<> to recognise 'polymorphism' of Factory<>
struct IBuild {
    virtual void* build() = 0;
};

template<typename Interface, typename AdapterType> struct Factory : IBuild {
    virtual void* build() override {
        return new AdapterType();
    }
};

template<typename AdapterType> void register_adapter() {

    typedef typename AdapterType::Interface Interface;
    typedef typename AdapterType::Adaptee Adaptee;

    //std::cout << "REGISTER " << typeid(AdapterType).name() << '\n';
    mapkey key = std::make_pair(Adaptee::data_type_id, &typeid(Interface));
    auto* factory = new Factory<Interface, AdapterType>();
    //std::cout << "FACTORY " << typeid(factory).name() << ' ' << factory << '\n';
    adapters.emplace(key, factory);
};

template<typename Interface, typename Adaptee> Interface* adapt(Adaptee* obj) {

    auto ti_interface = &typeid(Interface);
    auto ti_adaptee = obj->get_data_type_id();
    const auto key = std::make_pair(ti_adaptee, ti_interface);
    if (adapters.count(key) == 0) {
        std::cout << "NO ADAPTER FOUND";
        return nullptr;
    }

    IBuild* factory = static_cast<IBuild*>(adapters[key]);
    //std::cout << "FACTORY " << typeid(factory).name() << ' ' << factory << '\n';

    Adapter<Adaptee, Interface>* adapter = static_cast<Adapter<Adaptee, Interface>*>(factory->build());
    //std::cout << "ADAPTER " << typeid(adapter).name() << ' ' << adapter << '\n';
    adapter->setAdaptee(obj);
    // adapter already implements Interface
    return adapter;
};



