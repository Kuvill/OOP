#include <print>
#include "simple_property_changed_listener.hpp"
#include "simple_property_changing_listener.hpp"
#include "record_item.hpp"

class Label {
    SimplePropertyChangedListener<RecordItem> _listener;
    RecordItemNotified* _record;

public:
    Label( RecordItemNotified* record ) {
        _record = record;
        _record->add_property_listener( &_listener );
    }
};

class Box {
    SimplePropertyChangingListener<RecordItem> _listener;
    RecordItemControable* _record;

public:
    Box( RecordItemControable* record ) {
        _record = record;
        _record->add_property_listener( &_listener );
    }

};

int main() {
    { std::println( "onChanged implementation" );
        RecordItemNotified record( "firefox", 10 );
        Label label( &record );

        record.setAppName("");
        std::println( "Record after erasing name: {}, {}", record.getAppName(), record.getUptime() );
    }

    std::println( "-----------" );

    { std::println( "onChangin implementation" );
        RecordItemControable record( "firefox", 10 );
        Box box( &record );

        record.setAppName( "" );
        std::println( "Record after erasing name: {}, {}", record.getAppName(), record.getUptime() );
    }
}
