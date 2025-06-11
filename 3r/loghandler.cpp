#include "i_log_handler.hpp"
#include "handlers.hpp"

#include <iostream>
#include <fstream>
#include <stdexcept>

// socket
#include <sys/socket.h>
#include <sys/syslog.h>
#include <sys/un.h>
#include <unistd.h>

// syslogs
#include <syslog.h>

/* --- File Handler --- */

FileHandler::FileHandler( const std::string& fileName ) : _file(fileName) {}

void FileHandler::handle( const std::string& text ) {
	_file << text;
}

FileHandler::~FileHandler() = default;

/* --- Socket Handler --- */

SocketHandler::SocketHandler( const std::string& socketPath ) {
	_socket = socket( AF_UNIX, SOCK_STREAM, 0);
	if( _socket < 0 )
		throw std::runtime_error("couldn't create client fd for socket");

	sockaddr_un localAdr{};
	localAdr.sun_family = AF_UNIX;
	strcat( localAdr.sun_path, socketPath.c_str() );

	if( connect( _socket, reinterpret_cast<sockaddr*>(&localAdr),
			sizeof(localAdr)) < 0 )
		throw std::runtime_error("couldn't connect to a server socket");
}

void SocketHandler::handle( const std::string& text ) {
	if( send( _socket, text.c_str(), text.size(), 0 ) < 0 )
		throw std::runtime_error("couldn't send a message");
}

SocketHandler::~SocketHandler() {
	close( _socket );
}

/* --- Console Handler --- */

ConsoleHandler::ConsoleHandler( std::ostream& os ) : _os(os){}

void ConsoleHandler::handle( const std::string& text ) {
	_os << text;
}

/* --- SystemLog Handler --- */

SyslogHandler::SyslogHandler( const std::string appName ) : _appName(appName) {
	openlog( _appName.c_str(), LOG_PID, LOG_USER );
}

void SyslogHandler::handle( const std::string& text ) {
	syslog( LOG_INFO, "%s", text.c_str() );	
}

SyslogHandler::~SyslogHandler() {
	closelog();
}
