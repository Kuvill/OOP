#pragma once

#include <string>

class ILogFilter {
public:
	ILogFilter() = default;
	virtual ~ILogFilter() = default;
	virtual std::string match( const std::string& text ) = 0;
	
};

