#include <cassert>
#include <print>
#include <iostream>

import UserRepository;
import AuthService;


int main() {
    User usr;
    std::cout << "Input user. ({***} - optional. Entry '!' as filler)\nid name login password {email} {address}\n";
    std::cin >> usr;
    AuthService service;

    {
        UserRepository rep;

        rep.add( usr );
        std::cout << usr << '\n';
        // rep.update(1, {1, "Leo", "Kuvile", "qwerty", "ogo.com", "World"});
    }

    {
        UserRepository rep;

        auto us = rep.get_by_id(0);
        if( us )
            service.sign_in( us.value() );
        else 
            std::println( "error occured while logging" );
    }

    std::println( "uesr logined: {}", service.is_authorized() );
}

