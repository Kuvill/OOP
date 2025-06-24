module;

#include <optional>

export module IAuthService;

export import User;

export class IAuthService {
public:
    virtual ~IAuthService() = default;
    virtual void signIn(const User& user) = 0;
    virtual void signOut() = 0;
    virtual bool isAuthorized() const = 0;
    virtual std::optional<User> getCurrentUser() const = 0;
};

