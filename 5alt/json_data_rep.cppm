module;

#include <string>
#include <optional>
#include <fstream>
#include <vector>
#include <filesystem>

#include <nlohmann/json.hpp>

export module JsonDataRepository;

import IDataRepository;

using namespace std;
using namespace nlohmann;
namespace fs = std::filesystem;

export template <typename T>
class JsonDataRepository : public IDataRepository<T> {
public:
    JsonDataRepository(const string& filename) : filename(filename) {
        if (!fs::exists(filename)) {
            ofstream file(filename);
            file << "[]";
            file.close();
        }
    }

    virtual vector<T> getAll() override {
        ifstream file(filename);
        json j;
        file >> j;
        file.close();

        vector<T> items;
        for (const auto& item : j) {
            items.push_back(T::fromJson(item));
        }
        return items;
    }

    optional<T> getById(int id) override {
        auto items = getAll();
        for (const auto& item : items) {
            if (item.getId() == id) {
                return item;
            }
        }
        return nullopt;
    }

    void add(const T& item) override {
        auto items = getAll();
        items.push_back(item);
        saveAll(items);
    }

    void update(const T& item) override {
        auto items = getAll();
        bool found = false;
        for (auto& existingItem : items) {
            if (existingItem.getId() == item.getId()) {
                existingItem = item;
                found = true;
                break;
            }
        }
        if (!found) {
            throw runtime_error("Item not found for update");
        }
        saveAll(items);
    }

    void remove(const T& item) override {
        auto items = getAll();
        items.erase(remove_if(items.begin(), items.end(), 
            [&item](const T& existingItem) { 
                return existingItem.getId() == item.getId(); 
            }), items.end());
        saveAll(items);
    }

protected:
    virtual void saveAll(const vector<T>& items) {
        json j = json::array();
        for (const auto& item : items) {
            j.push_back(item.toJson());
        }

        ofstream file(filename);
        file << j.dump(4);
        file.close();
    }

private:
    string filename;
};

