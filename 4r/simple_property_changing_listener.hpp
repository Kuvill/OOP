#pragma once

#include "i_property_changing_listener.hpp"

#include <print>

template< typename T >
class SimplePropertyChangingListener : public IPropertyChangingListener {
public:
    bool onPropertyChanging( void* obj ) override;
};

template< typename T >
bool SimplePropertyChangingListener<T>::onPropertyChanging( void* obj ) {
    std::println( "object located in {} changed", (void*)&obj );
    std::println( "there is no additional condition to control the type ({})",
            typeid(T).name() );

    return true;
}

// template make it worser. should use just void* or base class or that hack
/*
    class FunctionPropertyChangedListener : public IPropertyChangedListener {
    public:
        template<typename T>
        FunctionPropertyChangedListener(std::function<void(T*)> callback)
            : m_callback([callback](void* obj) { callback(static_cast<T*>(obj)); }) {}
        
        void onPropertyChanged(void* obj) override {
            m_callback(obj);
        }

    private:
        std::function<void(void*)> m_callback;
    };
    @deepseek
*/
