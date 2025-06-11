module;

#include <nlohmann/json.hpp>

export module Save;

import Commands;

using namespace nlohmann;
using namespace std;

export class KeyboardMemento {
    json state;
public:
    KeyboardMemento(const json& s) : state(s) {}
    json getState() const { return state; }
};

export class KeyboardStateSaver {
public:
    static KeyboardMemento save(const map<string, shared_ptr<Command>>& keyMap) {
        json state;
        for (const auto& [key, cmd] : keyMap) {
            state["keyMap"][key] = cmd->getDescription();
        }
        
        state["buffer"] = PrintCharCommand::getBuffer();
        state["volume"] = VolumeUpCommand::getVolume();
        state["mediaPlaying"] = MediaPlayerCommand::getIsPlaying();
        
        return KeyboardMemento(state);
    }

    static void restore(map<string, shared_ptr<Command>>& keyMap, 
                       const KeyboardMemento& memento,
                       ostream& consoleOut,
                       ofstream& fileOut) {
        const json& state = memento.getState();
        
        keyMap.clear();
        
        if (state.contains("keyMap")) {
            for (const auto& [key, desc] : state["keyMap"].items()) {
                string description = desc.get<string>();
                
                if (description.find("Print") != string::npos) {
                    char c = description[7]; 
                    keyMap[key] = make_shared<PrintCharCommand>(c, consoleOut, fileOut);
                } else if (description == "Increase volume by 20%") {
                    keyMap[key] = make_shared<VolumeUpCommand>(consoleOut, fileOut);
                } else if (description == "Decrease volume by 20%") {
                    keyMap[key] = make_shared<VolumeDownCommand>(consoleOut, fileOut);
                } else if (description.find("media player") != string::npos) {
                    keyMap[key] = make_shared<MediaPlayerCommand>(consoleOut, fileOut);
                }
            }
        }
        
        if (state.contains("buffer")) {
            PrintCharCommand::setBuffer(state["buffer"].get<string>());
        }
        if (state.contains("volume")) {
            VolumeUpCommand::setVolume(state["volume"].get<int>());
        }
        if (state.contains("mediaPlaying")) {
            MediaPlayerCommand::setIsPlaying(state["mediaPlaying"].get<bool>());
        }
    }

    static void saveToFile(const KeyboardMemento& memento, const string& filename) {
        ofstream file(filename);
        if (file) {
            file << setw(4) << memento.getState() << endl;
        }
    }

    static KeyboardMemento loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file) {
            json state;
            file >> state;
            return KeyboardMemento(state);
        }
        return KeyboardMemento(json());
    }
};
