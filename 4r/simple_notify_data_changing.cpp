#include "i_notify_data_changing.hpp"

void SimpleNotifyDataChanging::add_property_listener( IPropertyChangingListener* listener ) {
    _listeners.insert( listener );
}

void SimpleNotifyDataChanging::remove_property_listener( IPropertyChangingListener* listener ) {
    _listeners.erase( listener );
}
