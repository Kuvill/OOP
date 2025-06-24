#include "logger.hpp"
#include "filters.hpp"
#include "handlers.hpp"

int main() {
	std::string text = "Warrning: mistake in classwork\n" \
			    "Fatal Error: Ishanov here\n" \
			    "Info: You died\n";


    try {

        { std::cout << "Simple Filter with Console output\n\t---\n\n";
            auto filter = std::make_shared<SimpleLogFilter>(LogLevel::Warn);
            auto handler = std::make_shared<ConsoleHandler>();
            Logger log( filter, handler);
            log.log( text );
        }

        { std::cout << "\n\n\t---\n\nRegex Filter with File Handler and Console\n";
            std::vector<Filter> filters;
            filters.emplace_back(std::make_shared<ReLogFilter>( std::regex(":[^:]*\n[^FI]*") ) );

            std::vector<Handler> handlers;
            handlers.emplace_back( std::make_shared<FileHandler>("regex.log") );
            handlers.emplace_back( std::make_shared<ConsoleHandler>() );
        
            Logger log( filters, handlers);
            log.log( text );
        }

    } catch( std::exception& e ) {
        std::cout << e.what() << ". Terminate...\n";
               
    }
}
