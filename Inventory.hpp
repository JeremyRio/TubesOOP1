#include <iostream>

#include "Item.hpp"
#define MAX_QTY 64
#define MAX_INVENTORY 27

class Inventory {
    private:
    Item** items;
    int size;

    public:
    Inventory() {
        size = 0;
        items = new Item*[MAX_INVENTORY];
        for (int i = 0; i < MAX_INVENTORY; i++) {
            items[i] = new Item();
        }
    }

    void Add(int idx, Item* item) {
        if (items[idx]->get_quantity() == 0) {
            delete items[idx];
            if (typeid(item) == typeid(Tool)) {
                items[idx] = new Tool(*(Tool*)item);
            } else {
                items[idx] = new NonTool(*(NonTool*)item);
            }
            this->size++;
        } else {
            // Stack atau Swap item
        }
    }

    Item& operator[](string id) {
        if (id[0] == 'I') {
            string temp;
            for (int i = 1; i < id.length(); i++) {
                temp += id[i];
            }
            int idx = stoi(temp);
            return *items[idx];
        }
    }

    Item& operator[](int idx) {
        return *items[idx];
    }

    void AddQuantity(int idx, int& remainder_qty) {
        int total_quantity = items[idx]->get_quantity() + remainder_qty;
        if (total_quantity > MAX_QTY) {
            remainder_qty = total_quantity - MAX_QTY;
            total_quantity = MAX_QTY;
        } else {
            remainder_qty = 0;
        }
        items[idx]->set_quantity(total_quantity);
    }

    int GetEmptySlot() {
        if (!this->isFull()) {
            for (int i = 0; i < MAX_INVENTORY; i++) {
                if (items[i]->get_quantity() == 0) {
                    return i;
                }
            }
        }
        return -1;
    }

    int FindItemNotFull(string item_name) {
        for (int i = 0; i < MAX_INVENTORY; i++) {
            if (items[i]->get_name() == item_name && items[i]->get_quantity() < MAX_QTY) {
                return i;
            }
        }
        return -1;
    }

    bool isFull() {
        return this->size == MAX_INVENTORY;
    }

    void Display() {
        for (int i = 0; i < MAX_INVENTORY; i++) {
            cout << "[ ";
            if (items[i]->get_quantity() > 0) {
                cout << items[i]->get_name() << " (" << items[i]->get_quantity() << ")";
            } else {
                cout << "EMPTY";
            }
            cout << " ]";
            if (i == 8 || i == 17) {
                cout << endl;
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
};