#include <iostream>
#include <map>
#include <vector>

#include "Item.hpp"
#include "NonTool.hpp"
#include "Recipes.hpp"
#include "Tool.hpp"
#define MAX_QTY 64
#define MAX_INVENTORY 27
#define MAX_CRAFT 9
#define CRAFT_BOUNDARY 3
#define CRAFTING_SLOT(i, j, k, l) (i * CRAFT_BOUNDARY + j + MAX_INVENTORY + k * CRAFT_BOUNDARY + l)
#define CRAFTING_INDEX(i) (MAX_INVENTORY + i)

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

    ~Inventory() {
        delete[] items;
    }

    bool IsEmpty(int idx) {
        return items[idx]->get_quantity() == 0;
    }

    static bool IsTool(Item* item) {
        // testing
        // cout << "Type id: " << typeid(*item).name() << endl;
        // cout << "Item Name: " << item->get_name() << endl;
        //
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
        ReplaceSlot(idx, item);
        this->size++;
    }

    void Add(int idx, Item* item, int durability) {
        ReplaceSlot(idx, item);
        this->size++;
        items[idx]->SetDurability(durability);
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
                this->Add(idx, new Item());
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
            return;
        }
        if (quantity > items[idxSource]->get_quantity()) {
            // throw Exception:
            // jumlah yang diminta untuk dipindah lebih dari jumlah item yang tersedia
            return;
        }
        if (IsEmpty(idxDest)) {  // Jika slot kosong, isi item
            ReplaceSlot(idxDest, items[idxSource]);
            items[idxSource]->remove_quantity(quantity);
            if (items[idxSource]->get_quantity() == 0) {
                this->size--;
            }
            items[idxDest]->set_quantity(quantity);
            this->size++;
        } else if (IsTool(items[idxSource]) || IsTool(items[idxDest])) {
            if (quantity != items[idxSource]->get_quantity() && !IsTool(items[idxSource])) {
                // throw Exception:
                // tidak dapat memindahkan sebagian item ke slot dengan item berbeda
                return;
            }
            Swap(idxSource, idxDest);
        } else if (items[idxSource]->get_id() != items[idxDest]->get_id()) {  // Keduanya NonTool, ID beda
            if (quantity != items[idxSource]->get_quantity()) {
                // throw Exception:
                // tidak dapat memindahkan sebagian item ke slot dengan item berbeda
                return;
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

    void GetItemCountInCrafting(int& item_count_tool, int& item_count_nontool) {
        for (int i = 0; i < MAX_CRAFT; i++) {
            if (items[MAX_INVENTORY + i]->get_quantity() > 0) {
                if (IsTool(items[MAX_INVENTORY + i])) {
                    item_count_tool++;
                } else {
                    item_count_nontool++;
                }
            }
        }
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

    void Give(string item_name, int item_qty, map<string, Item*>& item_map, int durability = 10) {
        if (item_map.find(item_name) != item_map.end()) {
            bool stop = false;
            int idx_item;
            while (item_qty > 0) {
                if (isFull() && !stop) {
                    // throw Exception:
                    // inventory sudah full, item terbuang: {item_qty}
                    stop = true;
                } else {
                    // jika item adalah tool
                    if (IsTool(item_map[item_name])) {
                        idx_item = GetEmptySlot();
                        if (idx_item != -1) {
                            if (durability == 10) {
                                Add(idx_item, item_map[item_name]);
                            } else {
                                Add(idx_item, item_map[item_name], durability);
                            }
                            item_qty--;
                        }
                    } else {
                        // jika item adalah nontool
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
            if (IsTool(items[idx]) && items[idx]->get_quantity() > 0) {
                items[idx]->Use();
            }
        } else {
            // throw Exception:
            // tidak ada ID inventory {inventory_id}
        }
    }

    void Crafting(map<int, vector<Recipes>> recipe_map, map<string, Item*>& item_map) {
        bool is_crafting = true;
        int item_count_tool = 0;
        int item_count_nontool = 0;
        GetItemCountInCrafting(item_count_tool, item_count_nontool);

        // testing
        cout << "item_count_tool: " << item_count_tool << endl;
        cout << "item_count_nontool: " << item_count_nontool << endl;
        //

        // jika slot tidak valid dimana terdapat campuran antara tool dan non tool di slot crafting
        while (is_crafting) {
            is_crafting = false;
            if (item_count_nontool > 0 && item_count_tool == 0 && recipe_map.find(item_count_nontool) != recipe_map.end()) {
                // jika hanya terdapat item nontool dalam crafting
                for (auto& recipe : recipe_map[item_count_nontool]) {
                    int i, j;
                    int recipe_row = recipe.GetRow();
                    int recipe_col = recipe.GetCol();
                    is_crafting = SubMatrix(recipe_row, recipe_col, recipe, item_map);
                    if (is_crafting) {
                        break;
                    }
                    // testing
                    // cout << "Recipe: " << recipe.GetName() << endl;
                }
            } else if (item_count_tool == 2 && item_count_nontool == 0) {
                // jika hanya terdapat item tool dalam crafting
                int idx_tool[2];
                GetIndexToolInCrafting(idx_tool);
                if (items[idx_tool[0]]->get_name() == items[idx_tool[1]]->get_name()) {
                    int total_durability = min(items[idx_tool[0]]->GetDurability() + items[idx_tool[1]]->GetDurability(), 10);
                    Give(items[idx_tool[0]]->get_name(), 1, item_map, total_durability);
                    Discard(idx_tool[0], 1);
                    Discard(idx_tool[1], 1);
                }
            } else {
                // jika crafting tidak valid yaitu terdapat campuran antara tool dan non tool di slot crafting atau tidak memenuhi kondisi di atas
            }
        }
    }

    void GetIndexToolInCrafting(int* idx_tool) {
        int idx = 0;
        for (int i = 0; i < MAX_CRAFT; i++) {
            int idx_crafting = i + MAX_INVENTORY;
            if (items[idx_crafting]->get_quantity() > 0) {
                idx_tool[idx++] = idx_crafting;
            }
        }
    }

    bool SubMatrix(int recipe_row, int recipe_col, Recipes recipe, map<string, Item*>& item_map) {
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
                            Discard(crafting_slot, 1);
                        }
                    }
                    int craft_quantity = recipe.GetCraftQuantity();
                    string name = recipe.GetName();
                    // testing
                    recipe.DisplayInfo();
                    cout << "Crafting: " << name << endl;
                    cout << "Quantity: " << craft_quantity << endl;
                    //
                    Give(name, craft_quantity, item_map);
                    return true;
                }
            }
        }
        return false;
    }

    bool InverseMatchRecipe(int i, int j, int recipe_row, int recipe_col, Recipes recipe) {
        for (int k = 0; k < recipe_row; k++) {
            for (int l = 0; l < recipe_col; l++) {
                int crafting_slot = CRAFTING_SLOT(i, j, k, l);
                int recipe_slot = k * recipe_col + recipe_col - l - 1;
                if (items[crafting_slot]->get_name() != recipe[recipe_slot] && items[crafting_slot]->get_type() != recipe[recipe_slot]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool MatchRecipe(int i, int j, int recipe_row, int recipe_col, Recipes recipe) {
        for (int k = 0; k < recipe_row; k++) {
            for (int l = 0; l < recipe_col; l++) {
                int crafting_slot = CRAFTING_SLOT(i, j, k, l);
                int recipe_slot = k * recipe_col + l;
                // testing
                // cout << "(i, j, k, l) = " << i << ", " << j << ", " << k << ", " << l << endl;
                // cout << "crafting_slot: I" << crafting_slot << endl;
                // cout << "recipe_slot: " << recipe_slot << endl;
                //
                if (items[crafting_slot]->get_name() != recipe[recipe_slot] && items[crafting_slot]->get_type() != recipe[recipe_slot]) {
                    return false;
                }
            }
        }
        return true;
    }
};