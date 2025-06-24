#include <cassert>
#include <print>

import Injector;
import Classes1;
import Classes2;

static constexpr bool IS_RELEASE_MODE = false;

using Class1 = std::conditional_t<IS_RELEASE_MODE, Class12, Class11>;
using Class2 = std::conditional_t<IS_RELEASE_MODE, Class22, Class21>;
using Class3 = std::conditional_t<IS_RELEASE_MODE, Class32, Class31>;

constexpr const char* msg = (IS_RELEASE_MODE) ?
            "Debug mode" : "Release Mode";

int main() {

    { std::println(msg);
        Injector inj;

        {
            inj.register_type<Interface1, Class1>( Lifestyle::Scoped) ;
            inj.register_type<Interface2, Class2>( Lifestyle::PerRequest );
            inj.register_type<Interface3, Class3>( Lifestyle::Singleton );

            std::println("Getting classes first time");
            inj.get_instance<Interface1>();
            inj.get_instance<Interface2>();
            inj.get_instance<Interface3>();
        }

        std::println("\nQuerring them after scope");
        inj.get_instance<Interface1>();
        inj.get_instance<Interface2>();
        inj.get_instance<Interface3>();

        std::println("\nAnd one more times");
        inj.get_instance<Interface1>();
        inj.get_instance<Interface2>();
        inj.get_instance<Interface3>();
    }

    std::println("\n------------------\n");


    { std::println("Test an implementation that takes args in contrucotr");
        Injector inj;

        inj.register_type<WithArgs, IntTaker>( Lifestyle::Scoped, 1 );
        inj.get_instance<WithArgs>();
    }
}
