#pragma once

#include <string>

class ILogHandler {
public:
	ILogHandler() = default;
	virtual ~ILogHandler() = default;
	virtual void handle( const std::string& text ) = 0;
};

