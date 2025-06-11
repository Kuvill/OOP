module;

#include <vector>
#include <optional>

export module IDataRepository;

export template< typename T >
struct IDataRepository {
    virtual ~IDataRepository() = default;

    // it is possable to use any iterator 
    // but require another one class system
    virtual std::vector<T> get() = 0;

    // c++ way - return iterator
    virtual const std::optional<T> get_by_id( int index ) = 0;

    virtual void add( const T& ) = 0;

    virtual void update( int index, const T& usr ) = 0;

    // delete - keyword
    virtual void remove( int inedx ) = 0;
};
