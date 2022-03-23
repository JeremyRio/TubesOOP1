#include "Item.hpp"

#include <iostream>

Item::Item() {
    this->id = 0;
    this->name = "-";
    this->type = "-";
    this->quantity = 0;
}

Item::Item(int id, string name, string type, int quantity) {
    this->id = id;
    this->name = name;
    this->type = type;
    this->quantity = quantity;
}

Item::Item(const Item &t) {
    this->id = t.id;
    this->name = t.name;
    this->quantity = t.quantity;
    this->type = t.type;
}

Item &Item::operator=(const Item &item) {
    this->id = item.id;
    this->name = item.name;
    this->quantity = item.quantity;
    this->type = item.type;
    return *this;
}

int Item::get_id() const {
    return this->id;
}

string Item::get_name() const {
    return this->name;
}

string Item::get_type() const {
    return this->type;
}

int Item::get_quantity() const {
    return this->quantity;
}

void Item::set_id(int id) {
    this->id = id;
}

void Item::set_name(string name) {
    this->name = name;
}

void Item::set_type(string type) {
    this->type = type;
}

void Item::set_quantity(int quantity) {
    this->quantity = quantity;
}

void Item::add_quantity(int quantity) {
    if (this->get_quantity() + quantity > MAX_QTY) {
        // throw Exception: item kelebihan
    }
    this->set_quantity(this->get_quantity() + quantity);
}

void Item::remove_quantity(int quantity) {
    if (this->get_quantity() - quantity < 0) {
        // throw Exception: item kekurangan
    }
    this->set_quantity(this->get_quantity() - quantity);

    if (this->get_quantity() == 0) {
        this->set_id(0);
        this->set_name("-");
        this->set_type("-");
    }
}

void Item::display_info() {
    // easier checking
    cout << "id: " << get_id() << "\n";
    cout << "Name: " << get_name() << "\n";
    cout << "Type: " << get_type() << "\n";
    cout << "Quantity: " << get_quantity() << "\n";
}

void Item::Use() {
    // do nothing
}

void Item::DisplayItem() {
    // do nothing
}

int Item::GetDurability() const {
    return 0;
}

void Item::SetDurability(int durability) {
    // do nothing
}