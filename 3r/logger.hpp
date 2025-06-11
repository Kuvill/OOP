#pragma once

#include "i_log_filter.hpp"
#include "i_log_handler.hpp"

#include <vector>
#include <memory>

using Filter = std::shared_ptr<ILogFilter>;
using Filters = std::vector<Filter>;

using Handler = std::shared_ptr<ILogHandler>;
using Handlers = std::vector<Handler>;

class Logger {
    Filters _filter;
    Handlers _handler;

public:
	Logger( const Filter&, const Handler& );
	Logger( const Filters&, const Handlers& );
	~Logger();
									
	void log( const std::string& text );
}; 
