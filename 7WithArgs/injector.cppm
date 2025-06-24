module;

#include <any>
#include <cassert>
#include <functional>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>
#include <vector>

export module Injector;

using namespace std;

struct CreatorBase {
    virtual ~CreatorBase() = default;
    virtual void* create( const std::vector<std::any>& args ) const = 0;
};

// Sorry, god...
template< typename Interface, typename Impl, typename... Args >
struct Creator : CreatorBase {
    void* create( const std::vector<std::any>& args ) const override {
        // should be an exception?
        assert( "Wrong amount of arguments passed to function!" && args.size() == sizeof...( Args ) );

        return construct( args, std::index_sequence_for<Args...>{} );
    }
private:
    template< std::size_t... Is >
        void* construct( const std::vector<std::any>& args, std::index_sequence<Is...> ) const {
            return new Impl( std::any_cast<Args>( args[Is] )... );

        }
};

export enum class Lifestyle {
    PerRequest,
    Scoped,
    Singleton
};

// *&*&*&*&*&*&*&*&
// i have to notice Injector about Scope memory free
export
struct Proxy {
    CreatorBase* &obj;
    Lifestyle style;

    Proxy( CreatorBase* &obj ) : obj(obj) {}
    Proxy( CreatorBase* &obj, Lifestyle style ) : obj(obj), style(style) {}

    ~Proxy() {
        if( style == Lifestyle::Scoped ) {
            delete obj;
            obj = nullptr;
        }
    }
};

// function - polymorphic thing. It allow to capture any values into lambda
using Factory = std::function<void*()>;

struct ImplInfo {
    Factory factory;
    Lifestyle style;
    CreatorBase* lastUsed = nullptr;
};

export
class Injector {
    std::unordered_map<std::type_index, ImplInfo> _creators;

public:
    template< typename Interface, typename Impl, typename... Args >
    void register_type( Lifestyle style, Args&&... args ) {
        std::vector<std::any> packedArgs = {std::forward<Args>(args)...};
        auto& creator = _creators[typeid(Interface)];

        creator.style = style;
        creator.factory = [packedArgs = std::move(packedArgs)]() {
            Creator<Interface, Impl, Args...> creator;
            return creator.create( packedArgs );
        };
    }

    template< typename Interface >
    Proxy get_instance() {
        auto it = _creators.find( typeid(Interface) );
        if( it == _creators.end() ) {
            std::string msg = "Interface not registered: ";
            msg += typeid( Interface ).name();
            throw std::runtime_error( msg );
        }

        auto& info = it->second;
        switch( it->second.style ){

            case Lifestyle::PerRequest:
                if( info.lastUsed != nullptr )
                    delete info.lastUsed;

                info.lastUsed = (CreatorBase*)info.factory();
                break;

            case Lifestyle::Scoped:
            case Lifestyle::Singleton:
                if( info.lastUsed == nullptr )
                   info.lastUsed = (CreatorBase*)info.factory();
 
                break;
        }

        return { info.lastUsed, info.style };
    }
};
