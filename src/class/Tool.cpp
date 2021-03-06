
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

int Tool::GetDurability() const {
    return this->durability;
}

void Tool::SetDurability(int durability) {
    this->durability = durability;
}

void Tool::AddDurability(int durability) {
    this->SetDurability(min(10, this->GetDurability() + durability));
}

void Tool::RemoveDurability(int durability) {
    this->SetDurability(max(0, this->GetDurability() - durability));
}

void Tool::DisplayInfo() {
    cout << "Item: Tool" << endl;
    Item::DisplayInfo();
    cout << "Durability: " << GetDurability() << endl;
}

void Tool::Use() {
    durability--;
    if (durability == 0) {
        cout << name << " breaks" << endl;
        RemoveQuantity(1);
    } else {
        cout << name << " is used, remaining durability: " << durability << endl;
    }
}

void Tool::DisplayItem() {
    cout << this->name << " "
         << " Durability: " << this->durability << endl;
}

void Tool::RemoveQuantity(int quantity) {
    this->SetQuantity(this->GetQuantity() - quantity);

    if (this->GetQuantity() == 0) {
        this->SetID(0);
        this->SetName("-");
        this->SetType("-");
        this->SetDurability(0);
    }
}
