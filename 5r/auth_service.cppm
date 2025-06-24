module;

#include <string>
#include <optional>
#include <fstream>

#include <nlohmann/json.hpp>

export module JsonAuthService;

import IAuthService;
import IUserRepository;

using namespace std;
using namespace nlohmann;
namespace fs = std::filesystem;

export class JsonAuthService : public IAuthService {
public:
    JsonAuthService(shared_ptr<IUserRepository> userRepo, const string& authFile)
        : userRepo(userRepo), authFile(authFile) {
        autoAuth();
    }

    void signIn(const User& user) override {
        currentUser = user;
        saveAuthState();
    }

    void signOut() override {
        currentUser.reset();
        clearAuthState();
    }

    bool isAuthorized() const override {
        return currentUser.has_value();
    }

    optional<User> getCurrentUser() const override {
        return currentUser;
    }

private:
    void autoAuth() {
        ifstream file(authFile);
        if (!file.is_open()) return;

        json j;
        try {
            file >> j;
            file.close();

            if (j.contains("login")) {
                auto login = j["login"].get<string>();
                auto user = userRepo->getByLogin(login);
                if (user && j.contains("password") && user->getPassword() == j["password"].get<string>()) {
                    currentUser = user;
                }
            }
        } catch (...) {
        }
    }

    void saveAuthState() {
        if (!currentUser) return;

        json j;
        j["login"] = currentUser->getLogin();
        j["password"] = currentUser->getPassword();

        ofstream file(authFile);
        file << j.dump(4);
        file.close();
    }

    void clearAuthState() {
        if (fs::exists(authFile)) {
            fs::remove(authFile);
        }
    }

    shared_ptr<IUserRepository> userRepo;
    string authFile;
    optional<User> currentUser;
};

