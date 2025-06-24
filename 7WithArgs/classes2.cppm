module;

#include <print>

export module Classes2;

export struct WithArgs {
    WithArgs( int a ) {
        std::print("WithArgs: ");
    }
};

export struct IntTaker : public WithArgs {
    IntTaker( int a ) : WithArgs( a ){
        std::println("IntTaker");
    }
};
