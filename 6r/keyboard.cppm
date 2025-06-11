module;

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>

export module Keyboard;

import Commands;
import Save;

using namespace std;

export class VirtualKeyboard {
    map<string, shared_ptr<Command>> keyMap;
    vector<shared_ptr<Command>> history;
    vector<shared_ptr<Command>> redoStack;
    ostream& consoleOut;
    ofstream fileOut;
    string filename;

    void setupDefaultKeyMap() {
        for (char c = 'a'; c <= 'z'; ++c) {
            string key(1, c);
            keyMap[key] = make_shared<PrintCharCommand>(c, consoleOut, fileOut);
        }
        
        keyMap["ctrl++"] = make_shared<VolumeUpCommand>(consoleOut, fileOut);
        keyMap["ctrl+-"] = make_shared<VolumeDownCommand>(consoleOut, fileOut);
        keyMap["ctrl+p"] = make_shared<MediaPlayerCommand>(consoleOut, fileOut);
    }

public:
    VirtualKeyboard(const string& outputFile, ostream& console = cout) 
        : consoleOut(console), filename(outputFile) {
        fileOut.open(outputFile);
        if (!fileOut) {
            throw runtime_error("Cannot open output file");
        }
        setupDefaultKeyMap();
    }

    ~VirtualKeyboard() {
        if (fileOut.is_open()) {
            fileOut.close();
        }
    }

    void pressKey(const string& key) {
        if (keyMap.find(key) != keyMap.end()) {
            keyMap[key]->execute();
            history.push_back(keyMap[key]);
            redoStack.clear();
        } else {
            consoleOut << "Unknown key: " << key << endl;
            fileOut << "Unknown key: " << key << endl;
        }
    }

    void addKeyCommand(const string& key, shared_ptr<Command> cmd) {
        keyMap[key] = cmd;
    }

    void undo() {
        if (!history.empty()) {
            auto cmd = history.back();
            cmd->undo();
            redoStack.push_back(cmd);
            history.pop_back();
        }
    }

    void redo() {
        if (!redoStack.empty()) {
            auto cmd = redoStack.back();
            cmd->redo();
            history.push_back(cmd);
            redoStack.pop_back();
        }
    }

    void saveState(const string& filename) {
        auto memento = KeyboardStateSaver::save(keyMap);
        KeyboardStateSaver::saveToFile(memento, filename);
    }

    void loadState(const string& filename) {
        auto memento = KeyboardStateSaver::loadFromFile(filename);
        KeyboardStateSaver::restore(keyMap, memento, consoleOut, fileOut);
    }

    void printCurrentState() const {
        consoleOut << "Current buffer: " << PrintCharCommand::getBuffer() << endl;
        consoleOut << "Current volume: " << VolumeUpCommand::getVolume() << "%" << endl;
        consoleOut << "Media player: " << (MediaPlayerCommand::getIsPlaying() ? "playing" : "stopped") << endl;
    }
};

