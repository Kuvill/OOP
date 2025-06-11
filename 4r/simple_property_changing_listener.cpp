#include "simple_property_changing_listener.hpp"
#include "record_item.hpp"

template<>
bool SimplePropertyChangingListener<RecordItem>::onPropertyChanging( void* obj ) {
    RecordItemControable* record = static_cast< RecordItemControable* >( obj );

    if( record->getAppName().size() == 0 ) {
        std::println( "Decline changes d:" );
        return false;
    }

    std::println( "object located in {} changed", (void*)&obj );
    return true;
}

