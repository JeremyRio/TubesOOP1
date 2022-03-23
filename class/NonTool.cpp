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
    if (item_source.GetID() != item_destination.GetID()) {
        BaseException *e = new CustomException("Item in source and destination have to be the same item");
        throw e;
        // throw Exception: ID item beda
    } else {
        if (item_source.GetQuantity() <= quantity) {
            int temp = quantity + item_destination.GetQuantity();
            if (temp > 64) {
                item_destination.SetQuantity(64);
                item_source.SetQuantity(item_source.GetQuantity() - quantity + temp - 64);
            } else {
                item_destination.SetQuantity(item_destination.GetQuantity() + quantity);
                item_source.SetQuantity(item_source.GetQuantity() - quantity);
            }
        } else {
            BaseException *e = new CustomException("Quantity is more than what is available");
            throw e;
            // throw Exception:
            // jumlah yang diminta buat dipindah lebih dari jumlah item yang ada
        }
    }
}

void NonTool::DisplayInfo() {
    // easier checking
    cout << "Item: "
         << "Non Tool" << endl;
    Item::DisplayInfo();
}

void NonTool::Use() {
    BaseException *e = new InvalidToolException(this->name);
    throw e;
    // throw Exception:
    // Item bukan merupakan tool
}

void NonTool::DisplayItem() {
    cout << this->name << " "
         << " Quantity: " << this->quantity << endl;
}