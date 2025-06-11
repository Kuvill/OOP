#pragma once

class IPropertyChangingListener {
public:
    virtual bool onPropertyChanging( void* obj ) = 0;
};
