#include "logger.hpp"

#include <iostream>

Logger::Logger( const Filter& filter, const Handler& handlers ) {
    _filter.push_back( filter );
}
Logger::Logger( const Filters& filters, const Handlers& handlers ) : _filter(filters), _handler(handlers) {}


Logger::~Logger() = default;

void Logger::log( const std::string& text ) {
    std::string result = text;
    for( auto& filter : _filter )
        result = filter->match( std::move(text) );


    for( auto& handler : _handler )
        handler->handle( result );

} 
