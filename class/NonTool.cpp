#include "NonTool.hpp"

#include <iostream>
using namespace std;

NonTool::NonTool()
    : Item() {
}

NonTool::NonTool(int id, string name, string type, int quantity)
    : Item(id, name, type, quantity) {
}

NonTool::NonTool(const NonTool &t)
    : Item(t) {
}

NonTool &NonTool::operator=(const NonTool &nt) {
    this->id = nt.id;
    this->name = nt.name;
    this->quantity = nt.quantity;
    this->type = nt.type;
    return *this;
}

void NonTool::Stack(Item item_source, int quantity, Item item_destination) {
    if (item_source.get_id() != item_destination.get_id()) {
        // throw Exception: ID item beda
    } else {
        if (item_source.get_quantity() <= quantity) {
            int temp = quantity + item_destination.get_quantity();
            if (temp > 64) {
                item_destination.set_quantity(64);
                item_source.set_quantity(item_source.get_quantity() - quantity + temp - 64);
            } else {
                item_destination.set_quantity(item_destination.get_quantity() + quantity);
                item_source.set_quantity(item_source.get_quantity() - quantity);
            }
        } else {
            // throw Exception:
            // jumlah yang diminta buat dipindah lebih dari jumlah item yang ada
        }
    }
}

void NonTool::display_info() {
    // easier checking
    cout << "Item: "
         << "Non Tool" << endl;
    Item::display_info();
}

void NonTool::Use() {
    // throw Exception:
    // Item bukan merupakan tool
}

void NonTool::DisplayItem() {
    cout << this->name << " "
         << " Quantity: " << this->quantity << endl;
}