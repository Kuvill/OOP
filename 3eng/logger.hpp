#pragma once

#include "i_log_filter.hpp"
#include "i_log_handler.hpp"

#include <vector>

class Logger {
    std::vector<ILogFilter> _filter;
    std::vector<ILogHandler> _handler;

public:
	Logger( ILogFilter*, ILogHandler* );
	~Logger();
									
	void log( const std::string& text );
}; 
