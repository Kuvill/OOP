module;

#include <typeindex>
#include <unordered_map>
#include <print>

export module Injector;

using namespace std;

export struct Base {
    virtual ~Base() = default;
};

export template< typename Type >
struct Wrapper : Base {
    Type obj;

    Type release() {
        return obj;
    }
};

export enum class Lifestyle {
    PerRequest,
    Scoped,
    Singleton
};

// *&*&*&*&*&*&*&*&
// i have to notice Injector about Scope memory free
struct Proxy {
    Base* &obj;
    Lifestyle style;

    Proxy( Base* &obj ) : obj(obj) {}
    Proxy( Base* &obj, Lifestyle style ) : obj(obj), style(style) {}

    ~Proxy() {
        if( style == Lifestyle::Scoped ) {
            delete obj;
            obj = nullptr;
        }
    }
};

using Factory = Base*(*)();


export template< typename Class >
Base* DefFactory() {
    return new Wrapper<Class>;
}

struct ImplInfo {
    Factory factory;
    Lifestyle style;
    Base* lastUsed = nullptr;
};

export class Injector {
    unordered_map<type_index, ImplInfo> _factory;

public:
    template< typename... Args >
    void registering( type_index interface, Factory implConstr, Lifestyle style, Args... args ) {
        _factory.insert_or_assign( interface, ImplInfo{implConstr, style, nullptr} );
    }

    Proxy get_instance( type_index interface ) {
        ImplInfo& info = _factory[interface];
        Proxy result( info.lastUsed );;

        switch( info.style ) {

            case Lifestyle::PerRequest:
                if( info.lastUsed != nullptr )
                    delete info.lastUsed;

                info.lastUsed = info.factory();
                break;

            case Lifestyle::Scoped:
            case Lifestyle::Singleton:
                if( info.lastUsed == nullptr )
                    info.lastUsed = info.factory();
        }

        result.obj = info.lastUsed;
        result.style = info.style;

        return result;
    } 
    
    ~Injector() {
        for( auto& node : _factory ) {
            if( node.second.lastUsed != nullptr ) {
                delete node.second.lastUsed;
            }
        }
    }

};
