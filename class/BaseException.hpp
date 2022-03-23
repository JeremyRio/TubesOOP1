#ifndef __BASE_EXCEPTION_HPP__
#define __BASE_EXCEPTION_HPP__

#include <iostream>
using namespace std;

class BaseException {
public:
    // menuliskan pesan kesalahan ke stdout
    virtual void printMessage() = 0;
};

class InvalidNumberException : public BaseException {
private:
    int number;
public:
    InvalidNumberException(int number) {
        this->number = number;
    }
    void printMessage() {
        cout << number << " is an invalid number" << endl;
    }
};

class InvalidItemException : public BaseException {
private:
    string item;
public:
    InvalidItemException(string item) {
        this->item = item;
    }
    void printMessage() {
        cout << "Item " << item << " doesn't exist" << endl;
    }
};

class InvalidCommandException : public BaseException {
private:
    string cmd;
public:
    InvalidCommandException(string cmd) {
        this->cmd = cmd;
    }
    void printMessage() {
        cout <<  cmd << " is an invalid command" << endl;
    }
};

class CommandFailedException {
private:
    BaseException** exc;
    int idx;
public:
    CommandFailedException() {
        exc = (BaseException**) malloc(sizeof(BaseException*));
        idx = 0;
    }
    void addException(BaseException* exc) {
        this->exc[idx] = exc;
        idx++;
    }
    void addException(CommandFailedException cmd) {
        for(int i = 0; i <= cmd.getIdx(); i++) {
            this->exc[idx] = cmd.exc[i];
            idx++;
        }
    }
    void printMessage() {
        cout << "Error Command with details:" << endl;
        for (int i = 0; i < idx; i++) {
            exc[i]->printMessage();
        }
    }

    int getIdx() {
        return idx;
    }
};

#endif