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
