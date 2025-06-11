#pragma once

#include "i_property_changed_listener.hpp"

#include <print>

template< typename T >
class SimplePropertyChangedListener : public IPropertyChangedListener {
public:
    void onPropertyChanged( void* obj ) override;
};

template< typename T >
void SimplePropertyChangedListener<T>::onPropertyChanged( void* obj ) {
    std::println("object located in {} changed", (void*)&obj );
}
