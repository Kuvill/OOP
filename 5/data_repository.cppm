module;

#include <cassert>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <vector>
#include <print>

export module DataRepository;

import IDataRepository;

const char* REP_PATH = "./rep";
const char* TMP_REP = "./rep.tmp";

export template< typename T >
class DataRepository final : IDataRepository<T> {
private:
    std::fstream _rep;
    size_t recordsCount = 0;

    std::string _path;
    std::string _tmpPath;

public:
    DataRepository( const char* path = REP_PATH ) {
        _path = path;
        _tmpPath = _path + ".tmp";
        _rep.open( _path, std::ios::in | std::ios::out | std::ios::app );
        assert( _rep.good() );
        assert( _rep.is_open() );

        recordsCount = std::count(std::istreambuf_iterator<char>(_rep), std::istreambuf_iterator<char>(), '\n');
        _rep.clear();
        _rep.seekg(0);
    }

    ~DataRepository() {
        _rep.flush();
        _rep.close();
    }

    std::vector<T> get() override {
        _rep.seekg( 0 );
        std::vector<T> result; result.reserve( recordsCount );
        T tmp;

        assert( _rep.good() );
        while( _rep >> tmp ) {
            result.push_back( std::move( tmp ) );
        }

        return result;
    }

    const std::optional<T> get_by_id( int id ) override {
        auto data = get();
        std::println( "Amount of users: {}", data.size() );
        
        auto it = std::find( data.begin(), data.end(), id );

        if( it != data.end() )
            return *it;

        return std::nullopt;
    }

    void add( const T& usr ) override {
        assert( _rep.good() );

        if( !get_by_id( usr.getId() ) ) {
            std::println("new user added");
            ++recordsCount;
            _rep.seekp( 0, std::ios::end );

            _rep << usr << '\n';
        } else 
            std::println("user skipped");

    }

    void update( int index, const T& usr ) override {
        if( recordsCount < index ) return;
        std::filesystem::rename( _path, _tmpPath );

        std::fstream newRep( _path );
        std::string buf;

        // index - 1 lines are the same as befor
        for( int i = 1; i < index; ++i ) {
            std::getline( _rep, buf );
            newRep.write( buf.c_str(), buf.size() );
        }

        newRep << usr;

        for( int i = index; i < recordsCount; ++i ) {
            std::getline( _rep, buf );
            newRep.write( buf.c_str(), buf.size() );
        }

        _rep.swap( newRep );
    }

    // delete - keyword
    void remove( int inedx ) override {
        if( recordsCount < inedx ) return;
        --recordsCount;

        std::filesystem::rename( _path, _tmpPath );

        std::fstream newRep( _path );
        std::string buf;

        // index - 1 lines are the same as befor
        for( int i = 1; i < inedx; ++i ) {
            std::getline( _rep, buf );
            newRep.write( buf.c_str(), buf.size() );
        }

        std::getline( _rep, buf );

        for( int i = inedx; i < recordsCount; ++i ) {
            std::getline( _rep, buf );
            newRep.write( buf.c_str(), buf.size() );
        }

        _rep.swap( newRep );
    }

};
