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

int Item::GetID() const {
    return this->id;
}

string Item::GetName() const {
    return this->name;
}

string Item::GetType() const {
    return this->type;
}

int Item::GetQuantity() const {
    return this->quantity;
}

void Item::SetID(int id) {
    this->id = id;
}

void Item::SetName(string name) {
    this->name = name;
}

void Item::SetType(string type) {
    this->type = type;
}

void Item::SetQuantity(int quantity) {
    this->quantity = quantity;
}

void Item::AddQuantity(int quantity) {
    if (this->GetQuantity() + quantity > MAX_QTY) {
        BaseException *e = new CustomException("Total quantity is too much");
        throw e;
        // throw Exception: item kelebihan
    }
    this->SetQuantity(this->GetQuantity() + quantity);
}

void Item::RemoveQuantity(int quantity) {
    this->SetQuantity(this->GetQuantity() - quantity);

    if (this->GetQuantity() == 0) {
        this->SetID(0);
        this->SetName("-");
        this->SetType("-");
    }
}

void Item::DisplayInfo() {
    // easier checking
    cout << "id: " << GetID() << "\n";
    cout << "Name: " << GetName() << "\n";
    cout << "Type: " << GetType() << "\n";
    cout << "Quantity: " << GetQuantity() << "\n";
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