#include "i_log_filter.hpp"

#include <regex>

// List of realisations

enum class LogLevel {
	All,
	Warn,
	Err
};


class SimpleLogFilter final : public ILogFilter {
	LogLevel _lvl;

public:
	SimpleLogFilter( LogLevel lvl );
	virtual ~SimpleLogFilter();

	std::string match( const std::string& text ) override;
};

class ReLogFilter final : public ILogFilter {
	std::regex _pattern;
public:
	ReLogFilter( const std::regex& pattern );
	virtual ~ReLogFilter();

	std::string match( const std::string& text ) override;
};

