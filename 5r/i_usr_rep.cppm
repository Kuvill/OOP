module;

#include <string>
#include <optional>

export module IUserRepository;

import IDataRepository;
import User;

export class IUserRepository {
public:
    virtual ~IUserRepository() = default;
    virtual std::optional<User> getByLogin(const std::string& login) = 0;
};

