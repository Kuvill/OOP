#pragma once

#include "i_notify_data_changed.hpp"
#include "i_notify_data_changing.hpp"

#include <string>

class RecordItem {
protected:
    std::string _appName;
    unsigned int _uptime;
public:
    RecordItem( const std::string& appName, unsigned int uptime)
            :_appName( appName ), _uptime( uptime ) {}

    virtual ~RecordItem() = default;

    virtual void setAppName( const std::string& );
    virtual std::string getAppName();

    virtual void setUptime( unsigned int );
    virtual unsigned int getUptime();
};

// --------------

class RecordItemNotified : public RecordItem, public SimpleNotifyDataChanged {
public:
    RecordItemNotified( const RecordItem& record ) : RecordItem(record) {}

    RecordItemNotified( const std::string& appName, unsigned int uptime)
            : RecordItem( appName, uptime ) {}

    virtual ~RecordItemNotified() = default;

    void setAppName( const std::string& ) override;
    std::string getAppName() override;

    void setUptime( unsigned int ) override;
    unsigned int getUptime() override;
};

// --------------

class RecordItemControable : public RecordItem, public SimpleNotifyDataChanging {
public:
    RecordItemControable( const RecordItem& record ) : RecordItem(record) {}

    RecordItemControable( const std::string& appName, unsigned int uptime)
            : RecordItem( appName, uptime ) {}

    virtual ~RecordItemControable() = default;

    void setAppName( const std::string& ) override;
    std::string getAppName() override;

    void setUptime( unsigned int ) override;
    unsigned int getUptime() override;
};
