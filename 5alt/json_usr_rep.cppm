module;

#include <string>
#include <optional>

export module JsonUserRepository;

import User;
import JsonDataRepository;
import IUserRepository;

using namespace std;

export class JsonUserRepository : public JsonDataRepository<User>, public IUserRepository {
public:
    JsonUserRepository(const string& filename) : JsonDataRepository<User>(filename) {}

    optional<User> getByLogin(const string& login) override {
        auto items = JsonDataRepository::getAll();
        for (const auto& item : items) {
            if (item.getLogin() == login) {
                return item;
            }
        }
        return nullopt;
    }
};
