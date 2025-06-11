#pragma once

#include "i_log_filter.hpp"
#include "i_log_handler.hpp"

class Logger {
	ILogFilter* _filter;
	ILogHandler* _handler;

public:
	Logger( ILogFilter*, ILogHandler* );
	~Logger();
									
	void log( const std::string& text );
}; 
