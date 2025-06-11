#include "i_log_handler.hpp"

#include <iostream>
#include <fstream>

// List of realisations

class FileHandler final : public ILogHandler {
	std::ofstream _file;

public:
	FileHandler( const std::string& fileName );

	void handle( const std::string& text ) override;

	~FileHandler();
}; 

// 

class SocketHandler final : public ILogHandler {
	int _socket;

public:
	SocketHandler( const std::string& socketPath );

	void handle( const std::string& text );

	~SocketHandler();
};

// 

class ConsoleHandler final : public ILogHandler {
	std::ostream& _os;

public:
	ConsoleHandler( std::ostream& os = std::cout );

	void handle( const std::string& text );
};

// 

class SyslogHandler final : public ILogHandler {
	std::string _appName;

public:
	SyslogHandler( const std::string appName );

	void handle( const std::string& text );

	~SyslogHandler();
};

