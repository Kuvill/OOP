module;

#include <vector>
#include <optional>

export module IDataRepository;

using namespace std;

export template <typename T>
class IDataRepository {
public:
    virtual ~IDataRepository() = default;
    virtual vector<T> getAll() = 0;
    virtual optional<T> getById(int id) = 0;
    virtual void add(const T& item) = 0;
    virtual void update(const T& item) = 0;
    virtual void remove(const T& item) = 0;
};
