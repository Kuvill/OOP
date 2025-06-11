#include "i_notify_data_changed.hpp"

void SimpleNotifyDataChanged::add_property_listener( IPropertyChangedListener* listener ) {
    _listeners.insert( listener );
}

void SimpleNotifyDataChanged::remove_property_listener( IPropertyChangedListener* listener ) {
    _listeners.erase( listener );
}

