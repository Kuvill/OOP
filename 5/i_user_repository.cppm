module;

#include <optional>
#include <string>

export module IUserRepository;

import User;

struct IUserRepository {
    virtual std::optional<User> get_by_login( const std::string& login) = 0;
};
