#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <cassert>

enum class Color {
    Red,
    Green,
    Default
};

static constexpr const char* getColorCode(Color color) {

	switch (color) {
		case Color::Red:
			return "\033[1;31m";
		case Color::Green:
			return "\033[1;32m";
		default:
			return "\033[0m";
	}
}

class Printer {
private:
    std::vector<std::string> _alphabet;
    int height, _power;
    Color _color;

public:
    Printer( std::string&& fileName, Color color ) : _color(color) {
        std::ifstream file( fileName );
        file >> _power >> height;

        if( !file.good() )
            throw std::runtime_error( "Wrong font file format!\nFirst line have to contain: power of alphabet, weight of an letter");

		std::string line;
		while (std::getline(file, line)) {
			_alphabet.emplace_back( std::move(line) );
		}
    }


    Printer( std::string&& fileName, Color color, char symbol) : Printer(std::move(fileName), color) {
		for (auto& row : _alphabet) {
			for (char& c : row) {
				if (c != ' ') {
					c = symbol;
				}
            }
        }
    }

    Printer( std::string&& fileName = "font.txt" ) : Printer( std::move(fileName), Color::Default ) {}

    void print(const std::string& text) {
        std::cout << getColorCode(_color);

        for (int i = 0; i < height; i++) {
            for (char c : text) {
                int charIndex = c - 'A';

                if (charIndex >= 0 && charIndex < _power) {
                    std::cout << _alphabet[i + charIndex * height];
                }

            }
            std::cout << std::endl;
        }
        std::cout << "\033[0m";
    }

	static void Print(std::string&& fileName, const std::string& text, Color color = Color::Default, char symbol = 0) {
		Printer printer(std::move(fileName), color, symbol);
		printer.print(text);
	}
};

int main() {
	Printer::Print( "font.txt", "HELLO", Color::Red, '*');

	std::cout << '\n';

    Printer myPrinter("small_font.txt", Color::Red);
    myPrinter.print("ABC");
    return 0;
}
