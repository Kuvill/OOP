#include <iostream>
#include <stdexcept>

import Commands;
import Save;
import Keyboard;

using namespace std;

int main() {
    try {
        VirtualKeyboard keyboard("output.txt");
        
        // Загружаем предыдущее состояние (если есть)
        ifstream testFile("keyboard_state.json");
        if (testFile.good()) {
            testFile.close();
            keyboard.loadState("keyboard_state.json");
        }
        
        // Пример использования
        keyboard.pressKey("a");
        keyboard.pressKey("b");
        keyboard.pressKey("c");
        keyboard.undo();
        keyboard.undo();
        keyboard.redo();
        keyboard.pressKey("ctrl++");
        keyboard.pressKey("ctrl+-");
        keyboard.pressKey("ctrl+p");
        keyboard.pressKey("d");
        keyboard.undo();
        keyboard.undo();
        
        // Сохраняем состояние перед выходом
        keyboard.saveState("keyboard_state.json");
        
        // Выводим текущее состояние
        keyboard.printCurrentState();
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
