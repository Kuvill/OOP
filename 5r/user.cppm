module;

#include <nlohmann/json.hpp>
#include <string>
#include <optional>

export module User;

using namespace nlohmann;
using namespace std;

export class User {
public:
    User(int id, const string& name, const string& login, const string& password,
         optional<string> email = nullopt, optional<string> address = nullopt)
        : id(id), name(name), login(login), password(password), email(email), address(address) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getLogin() const { return login; }
    string getPassword() const { return password; }
    optional<string> getEmail() const { return email; }
    optional<string> getAddress() const { return address; }

    void setName(const string& newName) { name = newName; }
    void setLogin(const string& newLogin) { login = newLogin; }
    void setPassword(const string& newPassword) { password = newPassword; }
    void setEmail(const optional<string>& newEmail) { email = newEmail; }
    void setAddress(const optional<string>& newAddress) { address = newAddress; }

    bool operator<(const User& other) const {
        return name < other.name;
    }

    string toString() const {
        stringstream ss;
        ss << "User{id=" << id 
           << ", name=" << name 
           << ", login=" << login;
        if (email) ss << ", email=" << *email;
        if (address) ss << ", address=" << *address;
        ss << "}";
        return ss.str();
    }

    json toJson() const {
        json j;
        j["id"] = id;
        j["name"] = name;
        j["login"] = login;
        j["password"] = password;
        if (email) j["email"] = *email;
        if (address) j["address"] = *address;
        return j;
    }

    static User fromJson(const json& j) {
        optional<string> email = j.contains("email") ? 
            optional<string>(j["email"].get<string>()) : nullopt;
        optional<string> address = j.contains("address") ? 
            optional<string>(j["address"].get<string>()) : nullopt;
        
        return User(
            j["id"].get<int>(),
            j["name"].get<string>(),
            j["login"].get<string>(),
            j["password"].get<string>(),
            email,
            address
        );
    }

private:
    int id;
    string name;
    string login;
    string password;
    optional<string> email;
    optional<string> address;
};
