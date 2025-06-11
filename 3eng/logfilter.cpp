#include "filters.hpp"

#include <algorithm>
#include <regex>


SimpleLogFilter::SimpleLogFilter( LogLevel lvl ) : _lvl(lvl) {}
SimpleLogFilter::~SimpleLogFilter() = default;

std::string SimpleLogFilter::match( const std::string& text ) {
	std::string result;
	if( _lvl == LogLevel::All ) return text;
	const char pattern = _lvl == LogLevel::Warn ?
						'W' : 'E';

	auto it = text.begin() + text.find('\n');
	if( text[0] == pattern )
		result.append( {text.begin(), it} );

	while( it++ != text.end() ) {

		if( *it == pattern ) {
			auto begin = it;
			it = std::find( it, text.end(), '\n' );
			result.append( {begin, it} ); 

		} else
			it = std::find( it, text.end(), '\n' );
	}

	return result;
}

ReLogFilter::ReLogFilter( const std::regex& pattern ) : _pattern(pattern) {}
ReLogFilter::~ReLogFilter() = default;

std::string ReLogFilter::match( const std::string& text ) {
	std::string result;

	auto matchBegin = std::sregex_iterator( text.begin(), text.end(), _pattern );
	auto matchEnd = std::sregex_iterator();

	while( matchBegin != matchEnd ) {
		result.append( matchBegin->str() );
        result.push_back( '\n' ); 
		++matchBegin;
	}

	return result;
}
