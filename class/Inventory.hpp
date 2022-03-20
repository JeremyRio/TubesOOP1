#include <iostream>
#include <map>

#include "Item.hpp"
#include "Tool.hpp"
#include "NonTool.hpp"
#define MAX_QTY 64
#define MAX_INVENTORY 27
#define MAX_CRAFT 9

class Inventory {
    private:
    Item** items;
    int size;

    public:
    Inventory() {
        size = 0;
        items = new Item*[MAX_INVENTORY + MAX_CRAFT];
        for (int i = 0; i < MAX_INVENTORY + MAX_CRAFT; i++) {
            items[i] = new Item();
        }
    }

    bool IsEmpty(int idx) {
        return items[idx]->get_quantity() == 0;
    }

    static bool IsTool(Item* item) {
        return (typeid(*item) == typeid(Tool));
    }

    void ReplaceSlot(int idx, Item* item) {
        delete items[idx];
        if (IsTool(item)) {
            items[idx] = new Tool(*(Tool*)item);
        } else {
            items[idx] = new NonTool(*(NonTool*)item);
        }
    }

    void Add(int idx, Item* item) {
        if (IsEmpty(idx)) {
            ReplaceSlot(idx, item);
            this->size++;
        } else {
            if (IsTool(items[idx]) || items[idx]->get_id() != item->get_id()) {
                // throw Exception:
                // Tidak dapat menambahkan item pada ID berbeda atau pada item Tool
            }
            items[idx]->add_quantity(item->get_quantity());
            // Stack atau Swap item
            // Komen: Kayaknya Stack atau Swap item bukan disini, tapi di Move
        }
    }

    void Discard(int idx, int item_qty) {
        if (IsEmpty(idx)) {
            // throw Exception;
            // Tidak ada item dalam slot tersebut
        } else if (item_qty > items[idx]->get_quantity()) {
            // throw Exception;
            // Jumlah item yang akan dibuang melebihi jumlah item yang ada
        } else {
            items[idx]->remove_quantity(item_qty);
            if (items[idx]->get_quantity() == 0) {
                this->size--;
            }
        }
    }

    // Swap isi dari 2 tempat di inventory/crafting table
    void Swap(int idxSource, int idxDest) {
        Item* temp;
        if (IsTool(items[idxDest])) {
            temp = new Tool(*(Tool*)items[idxDest]);
        } else {
            temp = new NonTool(*(NonTool*)items[idxDest]);
        }
        ReplaceSlot(idxDest, items[idxSource]);
        ReplaceSlot(idxSource, temp);
    }

    // Memindahkan suatu item dari suatu tempat ke tempat lain
    void Move(int idxSource, int quantity, int idxDest) {
        if (quantity == 0) {
            return;
        }
        // Tidak ada yang berubah, jumlah item yang dipindahkan sebanyak 0
        if (quantity < 0) {
            // throw Exception:
            // jumlah yang dipindahkan tidak boleh negatif
        }
        if (quantity > items[idxSource]->get_quantity()) {
            // throw Exception:
            // jumlah yang diminta untuk dipindah lebih dari jumlah item yang tersedia
        }
        if (IsEmpty(idxDest)) {  // Jika slot kosong, isi item
            items[idxSource]->remove_quantity(quantity);
            if (items[idxSource]->get_quantity() == 0) {
                this->size--;
            }
            ReplaceSlot(idxDest, items[idxSource]);
            items[idxDest]->set_quantity(quantity);
            this->size++;
        } else if (IsTool(items[idxSource]) || IsTool(items[idxDest])) {
            if (quantity != items[idxSource]->get_quantity() && !IsTool(items[idxSource])) {
                // throw Exception:
                // tidak dapat memindahkan sebagian item ke slot dengan item berbeda
            }
            Swap(idxSource, idxDest);
        } else if (items[idxSource]->get_id() != items[idxDest]->get_id()) {  // Keduanya NonTool, ID beda
            if (quantity != items[idxSource]->get_quantity()) {
                // throw Exception:
                // tidak dapat memindahkan sebagian item ke slot dengan item berbeda
            }
            Swap(idxSource, idxDest);
        } else {  // NonTool dengan ID sama
            if (items[idxDest]->get_quantity() == 64) {
                return;
            }
            // Tidak ada yang berubah, item tidak dapat di stack jika item pada destination sudah penuh
            // Stacking
            Stack(idxSource, quantity, idxDest);
        }
    }

    // Melakukan stacking, dipanggil di Move
    // Kondisi awal: NonTool dengan ID yang sama
    void Stack(int idxSource, int quantity, int idxDest) {
        if (items[idxDest]->get_quantity() + quantity > 64) {
            int maxAmountToMove = 64 - items[idxDest]->get_quantity();
            items[idxSource]->remove_quantity(maxAmountToMove);
            items[idxDest]->add_quantity(maxAmountToMove);
        } else {
            items[idxSource]->remove_quantity(quantity);
            if (items[idxSource]->get_quantity() == 0) {
                this->size--;
            }
            items[idxDest]->add_quantity(quantity);
        }
    }

    int GetIdx(string id) {
        string temp;
        for (int i = 1; i < id.length(); i++) {
            temp += id[i];
        }
        return stoi(temp);
    }

    Item* operator[](string id) {
        int idx_id = GetIdx(id);
        if (id[0] == 'I') {
            return items[idx_id];
        } else  // id[0] == 'C'
        {
            return items[idx_id + MAX_INVENTORY];
        }
    }

    Item* operator[](int idx) {
        return items[idx];
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
                if (IsEmpty(i)) {
                    return i;
                }
            }
        }
        return -1;
    }

    int FindItemNotFull(string item_name) {
        for (int i = 0; i < MAX_INVENTORY; i++) {
            if (items[i]->get_name() == item_name && items[i]->get_quantity() < MAX_QTY && !IsEmpty(i)) {
                return i;
            }
        }
        return -1;
    }

    bool isFull() {
        return this->size == MAX_INVENTORY;
    }

    void Display() {
        // Displaying Craft Table
        for (int i = MAX_INVENTORY; i < 36; i++) {
            cout << "[C " << (i - 27) << "]";
            if (i == 29 || i == 32 || i == 35) {
                cout << endl;
            }
        }
        cout << endl;
        // Displaying Inventory Slot
        for (int i = 0; i < MAX_INVENTORY; i++) {
            cout << "[I";
            if (i < 10) {
                cout << " ";
            }
            cout << i << "]";
            if (i == 8 || i == 17) {
                cout << endl;
            } else {
                cout << " ";
            }
        }
    }

    void Show() {
        Display();
        cout << endl
             << "\nCraft Slot" << endl;
        for (int i = MAX_INVENTORY; i < 36; i++) {
            if (items[i]->get_quantity() > 0) {
                cout << "C" << (i - MAX_INVENTORY) << " - ";
                items[i]->DisplayItem();
            }
            // else {cout << "EMPTY";}
        }
        cout << endl
             << "Inventory Slot" << endl;
        for (int i = 0; i < MAX_INVENTORY; i++) {
            if (items[i]->get_quantity() > 0) {
                cout << "I" << i << " - ";
                items[i]->DisplayItem();
            }
        }
    }

    void Give(string& item_name, int& item_qty, map<string, Item*>& item_map) {
        if (item_map.find(item_name) != item_map.end()) {
            bool stop = false;
            int idx_item;
            while (item_qty > 0 && !stop) {
                if (isFull()) {
                    // throw Exception:
                    // inventory sudah full, item terbuang: {item_qty}
                    stop = true;
                } else {
                    if (Inventory::IsTool(item_map[item_name])) {
                        idx_item = GetEmptySlot();
                        if (idx_item != -1) {
                            // item not found, add empty slot
                            Add(idx_item, item_map[item_name]);
                            item_qty--;
                        }
                    } else {
                        idx_item = FindItemNotFull(item_name);
                        if (idx_item == -1) {
                            idx_item = GetEmptySlot();
                            if (idx_item != -1) {
                                // item not found, add empty slot
                                Add(idx_item, item_map[item_name]);
                                AddQuantity(idx_item, item_qty);
                            }
                        } else {
                            // item found
                            AddQuantity(idx_item, item_qty);
                        }
                    }
                }
            }
        } else {
            // throw Exception:
            // Tidak ada nama Item {item_name}
        }
    }

    void Use(string inventory_id) {
        int idx = GetIdx(inventory_id);
        if (inventory_id[0] == 'I' && idx >= 0 && idx <= 27) {
            if (Inventory::IsTool(items[idx]) && items[idx]->get_quantity() > 0) {
                items[idx]->Use();
            }
        } else {
            // throw Exception:
            // tidak ada ID inventory {inventory_id}
        }
    }
};