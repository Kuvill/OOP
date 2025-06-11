#pragma once

#include "i_property_changed_listener.hpp"

#include <unordered_set>

class INotifyDataChanged {
public:
    virtual void add_property_listener( IPropertyChangedListener* ) = 0;
    virtual void remove_property_listener( IPropertyChangedListener* ) = 0;
};

class SimpleNotifyDataChanged : public INotifyDataChanged {
protected:
    std::unordered_set< IPropertyChangedListener* > _listeners;
public:

    void add_property_listener( IPropertyChangedListener* ) override;
    void remove_property_listener( IPropertyChangedListener* ) override;
};

