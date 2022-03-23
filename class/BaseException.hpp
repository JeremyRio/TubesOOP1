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
        cout << "Number " << number << " is not valid" << endl;
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
        cout << "Command " << cmd << " doesn't exist" << endl;
    }
};

class InvalidIDException : public BaseException {
    private:
    string id;

    public:
    InvalidIDException(string id) {
        this->id = id;
    }
    void printMessage() {
        cout << "ID " << id << " doesn't exist" << endl;
    }
};

class InventoryFullException : public BaseException {
    private:
    int quantity;
    string item_name;

    public:
    InventoryFullException(string item_name, int quantity) {
        this->quantity = quantity;
        this->item_name = item_name;
    }
    void printMessage() {
        printf("Iventory is full, %d %s is thrown\n", quantity, item_name);
    }
};

#endif