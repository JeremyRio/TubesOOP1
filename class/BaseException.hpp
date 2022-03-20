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
        cout << "Angka " << number << " tidak valid" << endl;
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
        cout << "Item bernama " << item << " tidak ada" << endl;
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
        cout << "Command " << cmd << " tidak ada" << endl;
    }
};

#endif