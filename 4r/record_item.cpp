#include "record_item.hpp"

#include <algorithm>

void RecordItem::setAppName( const std::string& appName ) {
    _appName = appName;
}

void RecordItem::setUptime( unsigned int uptime ) {
    _uptime = uptime;
}

std::string RecordItem::getAppName() {
    return _appName;
}

unsigned int RecordItem::getUptime() {
    return _uptime;
}

void RecordItemNotified::setAppName( const std::string& appName ) {
    _appName = appName;
    std::for_each( _listeners.begin(), _listeners.end(), [ this ]( IPropertyChangedListener* item ) {
        item->onPropertyChanged( this );
    });
}

void RecordItemNotified::setUptime( unsigned int uptime ) {
    _uptime = uptime;
    std::for_each( _listeners.begin(), _listeners.end(), [ this ]( IPropertyChangedListener* item ) {
        item->onPropertyChanged( this );           
    });
}

void RecordItemControable::setAppName( const std::string& appName ) {
    std::string oldValue = std::move( _appName );
    _appName = std::move(appName);

    std::for_each( _listeners.begin(), _listeners.end(), [ this, &oldValue ]( IPropertyChangingListener* item ) {
        if( !item->onPropertyChanging( this ) ) {
            _appName = std::move( oldValue );
            return;
        }
    });
}

void RecordItemControable::setUptime( unsigned int uptime ) {
    unsigned int oldValue = std::move( _uptime );
    _uptime = std::move( uptime );

    std::for_each( _listeners.begin(), _listeners.end(), [ this, &oldValue ]( IPropertyChangingListener* item ) {
        if( !item->onPropertyChanging( this ) ) {
            _uptime = std::move( oldValue );
            return;
        }
    });
}

std::string RecordItemNotified::getAppName() {
    return _appName;
}

unsigned int RecordItemNotified::getUptime() {
    return _uptime;
}

std::string RecordItemControable::getAppName() {
    return _appName;
}

unsigned int RecordItemControable::getUptime() {
    return _uptime;
}
