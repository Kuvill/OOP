#include <typeindex>
#include <print>

import Injector;
import Classes;

using namespace std;


// It is memory Safe EZ (since we don't overwrite interface impl. Can be easy fixed, but require some time)
int main() {
    
    std::println("Debug classes");
    {
        Injector inj;
        using Type = Debug;
        inj.registering(type_index( typeid(Interface1) ), BuildTypeFactory<Interface1, Type>, Lifestyle::PerRequest );
        inj.registering(type_index( typeid(Interface2) ), BuildTypeFactory<Interface2, Type>, Lifestyle::Scoped );
        inj.registering(type_index( typeid(Interface3) ), BuildTypeFactory<Interface3, Type>, Lifestyle::Singleton );

        auto a1 = inj.get_instance( type_index( typeid( Interface1 ) ) );
        auto a2 = inj.get_instance( type_index( typeid( Interface2 ) ) );
        auto a3 = inj.get_instance( type_index( typeid( Interface3 ) ) );

        if( !(a1.obj && a2.obj && a3.obj) )
            throw "some is null";
    }

    std::println("\n---\n");

    std::println("Release classes");
    {
        Injector inj;
        using Type = Debug;
        inj.registering(type_index( typeid(Interface1) ), BuildTypeFactory<Interface1, Type>, Lifestyle::PerRequest );
        inj.registering(type_index( typeid(Interface2) ), BuildTypeFactory<Interface2, Type>, Lifestyle::Scoped );

        auto a1 = inj.get_instance( type_index( typeid( Interface1 ) ) );
        auto a2 = inj.get_instance( type_index( typeid( Interface2 ) ) );
    }
}

