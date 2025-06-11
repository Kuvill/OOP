#pragma once

class IPropertyChangedListener {
public:
    virtual void onPropertyChanged( void* obj ) = 0;
};
