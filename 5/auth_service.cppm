module;

#include <filesystem>
#include <fstream>

export module AuthService;

import IAuthService;
import UserRepository;

const char* AUTH_PATH = "./.auth";

export class AuthService final : IAuthService {
private:
    std::fstream _auth;
    const std::string _path;

    void prepare_file() {
        _auth.close();
        std::filesystem::remove( _path );

    }

public:
    AuthService( const char* path = AUTH_PATH ) : _path( path ) {}

    void sign_in( const User& usr ) override {
        prepare_file();
        _auth.open( _path, std::ios::app );

        _auth << usr;

        _auth.close();
    }

    void sign_out() override {
        prepare_file();
    }

    bool is_authorized() override {
        User test;
        bool result;

        _auth.open( _path );

        result = bool( _auth >> test );

        _auth.close();

        return result;
            
    }   

    User current_user() override {
        User result;

        _auth.open( _path );

        _auth >> result;

        return result;
    }
    
};
