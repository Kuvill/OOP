#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
    Color _color;

public:
    Printer(Color color = Color::Default ) : _color(color) {
        std::ifstream file("font.txt");
		std::string line;

		while (std::getline(file, line)) {
			_alphabet.emplace_back( std::move(line) );
		}
    }

	// not optimal way
    Printer(Color color, char symbol) : Printer(color) {
		for (auto& row : _alphabet) {
			for (char& c : row) {
				if (c != ' ') {
					c = symbol;
				}
            }
        }
    }

    void print(const std::string& text) {
        std::cout << getColorCode(_color);

        for (int i = 0; i < 6; i++) {
            for (char c : text) {
                int charIndex = c - 'A';
                if (charIndex >= 0 && charIndex < 26) {
                    std::cout << _alphabet[i + charIndex * 6];
                }
            }
            std::cout << std::endl;
        }
        std::cout << "\033[0m";
    }

	static void Print(const std::string& text, Color color = Color::Default, char symbol = 0) {
		Printer printer(color, symbol);
		printer.print(text);
	}
};

int main() {
	Printer::Print("HELLO", Color::Red, '*');

	std::cout << '\n';

    Printer myPrinter(Color::Red);
    myPrinter.print("WORLD");
    return 0;
}
