
#include "Tool.hpp"

#include <iostream>
using namespace std;

Tool::Tool()
    : Item() {
}

Tool::Tool(int id, string name, string type, int durability)
    : Item(id, name, type, 1) {
    this->durability = durability;
}

Tool::Tool(const Tool &t)
    : Item(t) {
    this->durability = t.durability;
}

Tool &Tool::operator=(const Tool &t) {
    this->id = t.id;
    this->name = t.name;
    this->quantity = t.quantity;
    this->type = t.type;
    this->durability = t.durability;
    return *this;
}

int Tool::get_durability() const {
    return this->durability;
}

void Tool::set_durability(int durability) {
    this->durability = durability;
}

void Tool::add_durability(int durability) {
    this->set_durability(min(10, this->get_durability() + durability));
}

void Tool::remove_durability(int durability) {
    this->set_durability(max(0, this->get_durability() - durability));
}

void Tool::display_info() {
    cout << "Item: Tool" << endl;
    Item::display_info();
    cout << "Durability: " << get_durability() << endl;
}

void Tool::Use() {
    durability--;
    if (durability == 0) {
        quantity = 0;
    }
}

void Tool::DisplayItem() {
    cout << this->name << " "
         << " Durability: " << this->durability << endl;
}