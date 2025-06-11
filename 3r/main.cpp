#include "logger.hpp"
#include "filters.hpp"
#include "handlers.hpp"

int main() {
	std::string text = "Warrning: mistake in classwork\n" \
			    "Fatal Error: Ishanov here\n" \
			    "Info: You died\n";


	{ std::cout << "Simple Filter with Console output\n\t---\n\n";
		SimpleLogFilter filter(LogLevel::Warn);
		ConsoleHandler handler;
		Logger log( &filter, &handler);
		log.log( text );
	}

	{ std::cout << "\n\n\t---\n\nRegex Filter with File Handler\n";
		ReLogFilter filter( std::regex(":[^:]*\n[^FI]*") );
		// ReLogFilter filter( std::regex(": .*$") );
		FileHandler handler("regex.log");
		Logger log( &filter, &handler);
		log.log( text );
	}
}
