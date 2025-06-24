#include <iostream>
#include <stdexcept>

import Commands;
import Save;
import Keyboard;

using namespace std;

int main() {
    try {
        VirtualKeyboard keyboard("output.txt");
        
        ifstream testFile("keyboard_state.json");
        if (testFile.good()) {
            testFile.close();
            keyboard.loadState("keyboard_state.json");
        }

        std::string buf;
        while( std::getline( std::cin, buf ) ) {
            if( buf == "undo" )
                keyboard.undo();
            else if( buf == "redo" )
                keyboard.redo();
            else
                keyboard.pressKey(buf);
        }
        
        keyboard.saveState("keyboard_state.json");
        
        keyboard.printCurrentState();
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
