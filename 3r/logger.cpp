#include "logger.hpp"
#include <iostream>

Logger::Logger( ILogFilter* filter, ILogHandler* handler ) : _filter(filter), _handler(handler) {}

Logger::~Logger() = default;

void Logger::log( const std::string& text ) {
	_handler->handle( _filter->match( text ) );
}
