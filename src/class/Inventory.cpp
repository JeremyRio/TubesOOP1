#include "Inventory.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

Inventory::Inventory() {
    size = 0;
    items = new Item*[MAX_INVENTORY + MAX_CRAFT];
    for (int i = 0; i < MAX_INVENTORY + MAX_CRAFT; i++) {
        items[i] = new Item();
    }
}

Inventory::~Inventory() {
    delete[] items;
}

bool Inventory::IsEmptySlot(int idx) {
    return items[idx]->GetQuantity() == 0;
}

bool Inventory::IsTool(Item* item) {
    // testing
    // cout << "Type id: " << typeid(*item).name() << endl;
    // cout << "Item Name: " << item->GetName() << endl;
    //
    return (typeid(*item) == typeid(Tool));
}

void Inventory::ReplaceSlot(int idx, Item* item) {
    delete items[idx];
    if (IsTool(item)) {
        items[idx] = new Tool(*(Tool*)item);
    } else {
        items[idx] = new NonTool(*(NonTool*)item);
    }
}

void Inventory::Add(int idx, Item* item) {
    ReplaceSlot(idx, item);
    if (idx < MAX_INVENTORY) this->size++;
}

void Inventory::Add(int idx, Item* item, int durability) {
    ReplaceSlot(idx, item);
    if (idx < MAX_INVENTORY) this->size++;
    items[idx]->SetDurability(durability);
}

void Inventory::Discard(int idx, int item_qty) {
    if (IsEmptySlot(idx)) {
        // throw Exception;
        // Tidak ada item dalam slot tersebut
        BaseException* e = new CustomException("The selected item is empty");
        throw e;
    } else if (item_qty > items[idx]->GetQuantity()) {
        // throw Exception;
        // Jumlah item yang akan dibuang melebihi jumlah item yang ada
        BaseException* e = new CustomException("The selected item is out of stock");
        throw e;
    } else {
        items[idx]->RemoveQuantity(item_qty);
        if (items[idx]->GetQuantity() == 0 && idx < MAX_INVENTORY) {
            this->size--;
            this->Add(idx, new Item());
        }
    }
}

// Swap isi dari 2 tempat di inventory/crafting table
void Inventory::Swap(int idxSource, int idxDest) {
    Item* temp;
    if (IsTool(items[idxDest])) {
        temp = new Tool(*(Tool*)items[idxDest]);
    } else {
        temp = new NonTool(*(NonTool*)items[idxDest]);
    }
    ReplaceSlot(idxDest, items[idxSource]);
    ReplaceSlot(idxSource, temp);
    delete temp;
}

bool Inventory::ValidIndex(int idx) {
    return (idx >= 0 && idx <= 35);
}

// Memindahkan suatu item dari suatu tempat ke tempat lain
void Inventory::Move(int idxSource, int quantity, int idxDest) {
    if (!ValidIndex(idxSource) || !ValidIndex(idxDest)) {
        // throw Exception:
        // index out of bounds
        BaseException* e = new IndexOutOfBoundsException;
        throw e;
        return;
    }
    if (quantity == 0) {
        // DO NOTHING
        // Tidak ada yang berubah, jumlah item yang dipindahkan sebanyak 0
        return;
    }
    if (quantity < 0) {
        // throw Exception:
        // jumlah yang dipindahkan tidak boleh negatif
        BaseException* e = new InvalidNumberException(quantity);
        throw e;
        return;
    }
    if (quantity > items[idxSource]->GetQuantity()) {
        // throw Exception:
        // jumlah yang diminta untuk dipindah lebih dari jumlah item yang tersedia
        BaseException* e = new CustomException("The selected item is out of stock");
        throw e;
        return;
    }
    if (IsEmptySlot(idxDest)) {  // Jika slot kosong, isi item
        ReplaceSlot(idxDest, items[idxSource]);
        items[idxSource]->RemoveQuantity(quantity);
        if (items[idxSource]->GetQuantity() == 0 && idxSource < MAX_INVENTORY) {
            this->size--;
        }
        items[idxDest]->SetQuantity(quantity);
        if (idxDest < MAX_INVENTORY) this->size++;
    } else if (IsTool(items[idxSource]) || IsTool(items[idxDest])) {
        if (quantity != items[idxSource]->GetQuantity() && !IsTool(items[idxSource])) {
            // throw Exception:
            // tidak dapat memindahkan sebagian item ke slot dengan item berbeda
            BaseException* e = new CustomException("Item cannot be moved to different item");
            throw e;
            return;
        }
        Swap(idxSource, idxDest);
    } else if (items[idxSource]->GetID() != items[idxDest]->GetID()) {  // Keduanya NonTool, ID beda
        if (quantity != items[idxSource]->GetQuantity()) {
            // throw Exception:
            // tidak dapat memindahkan sebagian item ke slot dengan item berbeda
            BaseException* e = new CustomException("Item cannot be moved to different item");
            throw e;
            return;
        }
        Swap(idxSource, idxDest);
    } else {  // NonTool dengan ID sama
        if (items[idxDest]->GetQuantity() == 64) {
            // DO NOTHING
            // Tidak ada yang berubah, item tidak dapat di stack jika item pada destination sudah penuh
            return;
        }
        // Stacking
        Stack(idxSource, quantity, idxDest);
    }
}

// Melakukan stacking, dipanggil di Move
// Kondisi awal: NonTool dengan ID yang sama
void Inventory::Stack(int idxSource, int quantity, int idxDest) {
    if (items[idxDest]->GetQuantity() + quantity > 64) {
        int maxAmountToMove = 64 - items[idxDest]->GetQuantity();
        items[idxSource]->RemoveQuantity(maxAmountToMove);
        items[idxDest]->AddQuantity(maxAmountToMove);
    } else {
        items[idxSource]->RemoveQuantity(quantity);
        if (items[idxSource]->GetQuantity() == 0 && idxSource < MAX_INVENTORY) {
            this->size--;
        }
        items[idxDest]->AddQuantity(quantity);
    }
}

int Inventory::GetIdx(string id) {
    string temp;
    for (int i = 1; i < id.length(); i++) {
        temp += id[i];
    }
    return stoi(temp);
}

Item* Inventory::operator[](string id) {
    int idx_id = GetIdx(id);
    if (id[0] == 'I') {
        return items[idx_id];
    } else  // id[0] == 'C'
    {
        return items[idx_id + MAX_INVENTORY];
    }
}

Item* Inventory::operator[](int idx) {
    return items[idx];
}

void Inventory::AddQuantity(int idx, int& remainder_qty) {
    int total_quantity = items[idx]->GetQuantity() + remainder_qty;
    if (total_quantity > MAX_QTY) {
        remainder_qty = total_quantity - MAX_QTY;
        total_quantity = MAX_QTY;
    } else {
        remainder_qty = 0;
    }
    items[idx]->SetQuantity(total_quantity);
}

int Inventory::GetEmptySlot() {
    if (!this->IsFullInventory()) {
        for (int i = 0; i < MAX_INVENTORY; i++) {
            if (IsEmptySlot(i)) {
                return i;
            }
        }
    }
    return -1;
}

int Inventory::FindItemNotFull(string item_name) {
    for (int i = 0; i < MAX_INVENTORY; i++) {
        if (items[i]->GetName() == item_name && items[i]->GetQuantity() < MAX_QTY && !IsEmptySlot(i)) {
            return i;
        }
    }
    return -1;
}

bool Inventory::IsFullInventory() {
    return this->size == MAX_INVENTORY;
}

bool Inventory::IsEmptyInventory() {
    return this->size == 0;
}

void Inventory::GetItemCountInCrafting(int& item_count_tool, int& item_count_nontool) {
    for (int i = 0; i < MAX_CRAFT; i++) {
        if (items[MAX_INVENTORY + i]->GetQuantity() > 0) {
            if (IsTool(items[MAX_INVENTORY + i])) {
                item_count_tool++;
            } else {
                item_count_nontool++;
            }
        }
    }
}

void Inventory::Display() {
    // Displaying Craft Table
    cout << endl;
    cout << "   CRAFTING" << endl;
    for (int i = MAX_INVENTORY; i < 36; i++) {
        cout << "[C " << (i - 27) << "]";
        if (i == 29 || i == 32 || i == 35) {
            cout << endl;
        }
    }
    cout << endl;
    // Displaying Inventory Slot
    cout << "                   INVENTORY" << endl;
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

void Inventory::Show() {
    Display();
    cout << endl
         << "\n[CRAFT SLOT]" << endl;
    for (int i = MAX_INVENTORY; i < 36; i++) {
        if (items[i]->GetQuantity() > 0) {
            cout << "C" << (i - MAX_INVENTORY) << " - ";
            items[i]->DisplayItem();
        }
    }

    cout << endl
         << "[INVENTORY SLOT]" << endl;
    for (int i = 0; i < MAX_INVENTORY; i++) {
        if (items[i]->GetQuantity() > 0) {
            cout << "I" << i << " - ";
            items[i]->DisplayItem();
        }
    }
}

void Inventory::Give(string item_name, int item_qty, map<string, Item*>& item_map, int durability) {
    int initial_quantity = item_qty;
    if (item_map.find(item_name) != item_map.end()) {
        int idx_item;
        while (item_qty > 0) {
            // Jika item berupa tool
            if (IsTool(item_map[item_name])) {
                idx_item = GetEmptySlot();
                if (idx_item != -1) {
                    if (durability == 10) {
                        Add(idx_item, item_map[item_name]);
                    } else {
                        Add(idx_item, item_map[item_name], durability);
                    }
                    item_qty--;
                } else {
                    BaseException* e = new InventoryFullException(item_name, item_qty);
                    throw e;
                }
            } else {
                // Jika item berupa nontool
                idx_item = FindItemNotFull(item_name);
                if (idx_item == -1) {
                    idx_item = GetEmptySlot();
                    if (idx_item != -1) {
                        // item not found, add empty slot
                        Add(idx_item, item_map[item_name]);
                        AddQuantity(idx_item, item_qty);
                    } else {
                        BaseException* e = new InventoryFullException(item_name, item_qty);
                        throw e;
                    }
                } else {
                    // item found
                    AddQuantity(idx_item, item_qty);
                }
            }
        }
    } else {
        // throw Exception:
        // item not found: {item_name}
        BaseException* e = new InvalidItemException(item_name);
        throw e;
    }
}

void Inventory::Use(string inventory_id) {
    int idx = GetIdx(inventory_id);
    if (inventory_id[0] == 'I' && idx >= 0 && idx <= 27) {
        if (items[idx]->GetQuantity() > 0) {
            items[idx]->Use();
        } else {
            BaseException* e = new CustomException("Selected item is empty");
            throw e;
        }
    } else {
        // throw Exception:
        // tidak ada ID inventory {inventory_id}
        BaseException* e = new InvalidIDException(inventory_id);
        throw e;
    }
}

void Inventory::Crafting(map<int, vector<Recipes>> recipe_map, map<string, Item*>& item_map) {
    bool is_crafting = true;
    int item_count_tool = 0;
    int item_count_nontool = 0;
    int amount_crafted = 0;
    bool is_nontool_crafting = false;
    string recipe_name;
    GetItemCountInCrafting(item_count_tool, item_count_nontool);

    // testing
    // cout << "item_count_tool: " << item_count_tool << endl;
    // cout << "item_count_nontool: " << item_count_nontool << endl;
    //

    if (item_count_nontool > 0 && item_count_tool == 0 && recipe_map.find(item_count_nontool) != recipe_map.end()) {
        is_nontool_crafting = true;
        // jika hanya terdapat item nontool dalam crafting
        for (auto& recipe : recipe_map[item_count_nontool]) {
            int i, j;
            int recipe_row = recipe.GetRow();
            int recipe_col = recipe.GetCol();
            recipe_name = recipe.GetName();
            is_crafting = SubMatrix(recipe_row, recipe_col, recipe, item_map);
            while (is_crafting) {
                amount_crafted += recipe.GetCraftQuantity();
                is_crafting = SubMatrix(recipe_row, recipe_col, recipe, item_map);
            }
            if (amount_crafted > 0) {
                break;
            }
        }
    } else if (item_count_tool == 2 && item_count_nontool == 0) {
        // jika hanya terdapat item tool dalam crafting
        int idx_tool[2];
        bool tool_combined = false;
        string name;
        int total_durability;
        GetIndexToolInCrafting(idx_tool);
        if (items[idx_tool[0]]->GetName() == items[idx_tool[1]]->GetName()) {
            total_durability = min(items[idx_tool[0]]->GetDurability() + items[idx_tool[1]]->GetDurability(), 10);
            Give(items[idx_tool[0]]->GetName(), 1, item_map, total_durability);
            tool_combined = true;
            name = items[idx_tool[0]]->GetName();
            Discard(idx_tool[0], 1);
            Discard(idx_tool[1], 1);
        }
        if (!tool_combined) {
            BaseException* e = new CustomException("Tools cannot be combined");
            throw e;
        } else {
            cout << "Successfully combined 2 " << name << ", total durability: " << total_durability << endl;
        }
    } else {
        // jika crafting tidak valid yaitu terdapat campuran antara tool dan non tool di slot crafting atau tidak memenuhi kondisi di atas
        BaseException* e = new CustomException("Crafting is not valid");
        throw e;
    }

    if (amount_crafted > 0) {
        cout << "Successfully crafted " << amount_crafted << " " << recipe_name << endl;
    } else if (is_nontool_crafting) {
        BaseException* e = new CustomException("Crafting failed, no recipes matched the crafting pattern");
        throw e;
    }
}

void Inventory::GetIndexToolInCrafting(int* idx_tool) {
    int idx = 0;
    for (int i = 0; i < MAX_CRAFT; i++) {
        int idx_crafting = i + MAX_INVENTORY;
        if (items[idx_crafting]->GetQuantity() > 0) {
            idx_tool[idx++] = idx_crafting;
        }
    }
}

bool Inventory::SubMatrix(int recipe_row, int recipe_col, Recipes recipe, map<string, Item*>& item_map) {
    for (int i = 0; i + recipe_row - 1 < CRAFT_BOUNDARY; i++) {
        for (int j = 0; j + recipe_col - 1 < CRAFT_BOUNDARY; j++) {
            bool match = MatchRecipe(i, j, recipe_row, recipe_col, recipe);
            if (!match) {
                match = InverseMatchRecipe(i, j, recipe_row, recipe_col, recipe);
            }
            if (match) {
                for (int k = 0; k < recipe_row; k++) {
                    for (int l = 0; l < recipe_col; l++) {
                        int crafting_slot = CRAFTING_SLOT(i, j, k, l);
                        if (!IsEmptySlot(crafting_slot)) Discard(crafting_slot, 1);
                    }
                }
                int craft_quantity = recipe.GetCraftQuantity();
                string name = recipe.GetName();
                // testing
                // recipe.DisplayInfo();
                // cout << "Crafting: " << name << endl;
                // cout << "Quantity: " << craft_quantity << endl;
                //
                Give(name, craft_quantity, item_map);
                return true;
            }
        }
    }
    return false;
}

bool Inventory::InverseMatchRecipe(int i, int j, int recipe_row, int recipe_col, Recipes recipe) {
    for (int k = 0; k < recipe_row; k++) {
        for (int l = 0; l < recipe_col; l++) {
            int crafting_slot = CRAFTING_SLOT(i, j, k, l);
            int recipe_slot = k * recipe_col + recipe_col - l - 1;
            if (items[crafting_slot]->GetName() != recipe[recipe_slot] && items[crafting_slot]->GetType() != recipe[recipe_slot]) {
                return false;
            }
        }
    }
    return true;
}

bool Inventory::MatchRecipe(int i, int j, int recipe_row, int recipe_col, Recipes recipe) {
    for (int k = 0; k < recipe_row; k++) {
        for (int l = 0; l < recipe_col; l++) {
            int crafting_slot = CRAFTING_SLOT(i, j, k, l);
            int recipe_slot = k * recipe_col + l;
            // testing
            // cout << "(i, j, k, l) = " << i << ", " << j << ", " << k << ", " << l << endl;
            // cout << "crafting_slot: I" << crafting_slot << endl;
            // cout << "recipe_slot: " << recipe_slot << endl;
            //
            if (items[crafting_slot]->GetName() != recipe[recipe_slot] && items[crafting_slot]->GetType() != recipe[recipe_slot]) {
                return false;
            }
        }
    }
    return true;
}

void Inventory::Exporting(string file_name) {
    string full = "";
    string path = "exports/" + file_name;
    string convert1, convert2;
    int temp1, temp2;
    for (int i = 0; i < MAX_INVENTORY; i++) {
        temp1 = items[i]->GetID();
        if (IsTool(items[i])) {
            temp2 = items[i]->GetDurability();
        } else {
            temp2 = items[i]->GetQuantity();
        }
        convert1 = to_string(temp1);
        convert2 = to_string(temp2);
        full += convert1 + ":" + convert2 + "\n";
    }
    ofstream MyFile(path);
    MyFile << full;
    MyFile.close();
    cout << file_name << " successfully exported" << endl;
}