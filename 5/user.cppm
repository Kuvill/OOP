module;

#include <print>
#include <string>
#include <iostream>
#include <iosfwd>

export module User;

export class User {
    unsigned int id;
    std::string name;
    std::string login;
    std::string passwd;

    std::string email;
    std::string address;

public:
    User(){}

    User(int id, const std::string& name, const std::string& login, const std::string& passwd,
         const std::string& email = "", const std::string& address = "" )
        : id(id), name(name), login(login), passwd(passwd), email(email), address(address) {}

    int getId() const { return id; }

    bool operator<( const User& other ) const {
        return name < other.name;
    }

    bool operator==( const int id ) const {
        return this->id == id;
    }

    friend std::ostream& operator<<( std::ostream& os, const User& usr );
    friend std::istream& operator>>( std::istream& os, User& usr );
};

std::ostream& operator<<( std::ostream& os, const User& usr ) {
    std::cout << "called operator<<\n";
    os << usr.id << ' ' << usr.name << ' ' << usr.login << ' ' <<
        usr.passwd << ' ' << (usr.email.empty() ? "!" : usr.email) << ' ' <<
        (usr.address.empty() ? "!" : usr.address);

    return os;
}

std::istream& operator>>( std::istream& is, User& usr ) {
    char tmp;
    is >> usr.id >> usr.name >> usr.login >> usr.passwd;

    tmp = is.peek();
    if( tmp == '!' ) is.get();
    else is >> usr.email;

    tmp = is.peek();
    if( tmp == '!' ) is.get();

    return is;
}
