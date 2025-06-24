module;

#include <print>

export module Classes1;

 export struct Debug {};
 export struct Release {};

export struct Interface1 {
    Interface1() {
        std::print( "created Interface1:" );
    }

    virtual ~Interface1() {}
};
export struct Interface2 {
    Interface2() {
        std::print( "created Interface1:" );
    }

    virtual ~Interface2() {}

};
export struct Interface3 {
    Interface3() {
        std::print( "created Interface1:" );
    }

    virtual ~Interface3() {}

};

export struct Class11 final : Interface1 {
    Class11() {
        std::println( "Class11" );
    } 

~Class11() override {
        std::println("~Class11");
    }
};
export struct Class12 final : Interface1 {
    Class12() {
        std::println( "Class12" );
    }

~Class12() {
        std::println( "~Class12" );
    }
};

export struct Class21 final : Interface2 {
    Class21() {
        std::println( "Class21" );
    }

~Class21() override {
        std::println( "~Class21" );
        
    }
};
export struct Class22 final : Interface2 {
    Class22() {
        std::println( "Class22" );
    }

~Class22() override {
        std::println( "~Class22" );
        
    }
};

export struct Class31 final : Interface3 {
    Class31() {
        std::println( "Class31" );
    }

~Class31() override {
        std::println( "~Class31" );
        
    }
};
export struct Class32 final : Interface3 {
    Class32() {
        std::println( "Class32" );
    }

~Class32() override {
        std::println( "~Class21" );
        
    }
};


