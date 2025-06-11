#pragma once

#include "i_property_changing_listener.hpp"

#include <unordered_set>

class INotifyDataChanging {
public:
    virtual void add_property_listener( IPropertyChangingListener* ) = 0;
    virtual void remove_property_listener( IPropertyChangingListener* ) = 0;
};

class SimpleNotifyDataChanging : public INotifyDataChanging {
protected:
    std::unordered_set< IPropertyChangingListener* > _listeners;
public:

    void add_property_listener( IPropertyChangingListener* ) override;
    void remove_property_listener( IPropertyChangingListener* ) override;
};

