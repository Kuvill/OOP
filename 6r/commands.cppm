module;

#include <string>
#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>

export module Commands;

using namespace std;

export class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual string getDescription() const = 0;
};

export class PrintCharCommand : public Command {
    char character;
    static string buffer;
    ostream& consoleOut;
    ofstream& fileOut;
public:
    PrintCharCommand(char c, ostream& console, ofstream& file) 
        : character(c), consoleOut(console), fileOut(file) {}

    void execute() override {
        buffer += character;
        consoleOut << character << endl;
        fileOut << buffer << endl;
    }

    void undo() override {
        if (!buffer.empty()) {
            buffer.pop_back();
            consoleOut << "undo" << endl;
            fileOut << buffer << endl;
        }
    }

    void redo() override {
        buffer += character;
        consoleOut << "redo" << endl;
        fileOut << buffer << endl;
    }

    string getDescription() const override {
        return string("Print '") + character + "'";
    }

    static string getBuffer() { return buffer; }
    static void setBuffer(const string& newBuffer) { buffer = newBuffer; }
};
string PrintCharCommand::buffer = "";

export class VolumeUpCommand : public Command {
    static int volume;
    ostream& consoleOut;
    ofstream& fileOut;
public:
    VolumeUpCommand(ostream& console, ofstream& file) 
        : consoleOut(console), fileOut(file) {}

    void execute() override {
        volume += 20;
        if (volume > 100) volume = 100;
        consoleOut << "volume increased +20%" << endl;
        fileOut << "volume increased +20%" << endl;
    }

    void undo() override {
        volume -= 20;
        if (volume < 0) volume = 0;
        consoleOut << "volume decreased +20%" << endl;
        fileOut << "volume decreased +20%" << endl;
    }

    void redo() override {
        execute();
    }

    string getDescription() const override {
        return "Increase volume by 20%";
    }

    static int getVolume() { return volume; }
    static void setVolume(int vol) { volume = vol; }
};
int VolumeUpCommand::volume = 50;

export class VolumeDownCommand : public Command {
    ostream& consoleOut;
    ofstream& fileOut;
public:
    VolumeDownCommand(ostream& console, ofstream& file) 
        : consoleOut(console), fileOut(file) {}

    void execute() override {
        VolumeUpCommand::setVolume(VolumeUpCommand::getVolume() - 20);
        if (VolumeUpCommand::getVolume() < 0) VolumeUpCommand::setVolume(0);
        consoleOut << "volume decreased +20%" << endl;
        fileOut << "volume decreased +20%" << endl;
    }

    void undo() override {
        VolumeUpCommand::setVolume(VolumeUpCommand::getVolume() + 20);
        if (VolumeUpCommand::getVolume() > 100) VolumeUpCommand::setVolume(100);
        consoleOut << "volume increased +20%" << endl;
        fileOut << "volume increased +20%" << endl;
    }

    void redo() override {
        execute();
    }

    string getDescription() const override {
        return "Decrease volume by 20%";
    }
};

export class MediaPlayerCommand : public Command {
    static bool isPlaying;
    ostream& consoleOut;
    ofstream& fileOut;
public:
    MediaPlayerCommand(ostream& console, ofstream& file) 
        : consoleOut(console), fileOut(file) {}

    void execute() override {
        isPlaying = true;
        consoleOut << "media player launched" << endl;
        fileOut << "media player launched" << endl;
    }

    void undo() override {
        isPlaying = false;
        consoleOut << "media player closed" << endl;
        fileOut << "media player closed" << endl;
    }

    void redo() override {
        execute();
    }

    string getDescription() const override {
        return isPlaying ? "Close media player" : "Launch media player";
    }

    static bool getIsPlaying() { return isPlaying; }
    static void setIsPlaying(bool playing) { isPlaying = playing; }
};
bool MediaPlayerCommand::isPlaying = false;
