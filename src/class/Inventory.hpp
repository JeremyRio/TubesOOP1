#include <iostream>
#include <map>
#include <vector>

#include "BaseException.hpp"
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
    Inventory();
    ~Inventory();
    bool IsEmptySlot(int idx);
    bool IsTool(Item* item);
    void ReplaceSlot(int idx, Item* item);
    void Add(int idx, Item* item);
    void Add(int idx, Item* item, int durability);
    void Discard(int idx, int item_qty);

    // Swap isi dari 2 tempat di inventory/crafting table
    void Swap(int idxSource, int idxDest);

    bool ValidIndex(int idx);

    // Memindahkan suatu item dari suatu tempat ke tempat lain
    void Move(int idxSource, int quantity, int idxDest);

    // Melakukan stacking, dipanggil di Move
    // Kondisi awal: NonTool dengan ID yang sama
    void Stack(int idxSource, int quantity, int idxDest);

    int GetIdx(string id);
    Item* operator[](string id);
    Item* operator[](int idx);
    void AddQuantity(int idx, int& remainder_qty);
    int GetEmptySlot();

    int FindItemNotFull(string item_name);

    bool IsFullInventory();
    bool IsEmptyInventory();
    void GetItemCountInCrafting(int& item_count_tool, int& item_count_nontool);

    void Display();
    void Show();

    void Give(string item_name, int item_qty, map<string, Item*>& item_map, int durability = 10);

    void Use(string inventory_id);

    void Crafting(map<int, vector<Recipes>> recipe_map, map<string, Item*>& item_map);
    void GetIndexToolInCrafting(int* idx_tool);
    bool SubMatrix(int recipe_row, int recipe_col, Recipes recipe, map<string, Item*>& item_map);
    bool InverseMatchRecipe(int i, int j, int recipe_row, int recipe_col, Recipes recipe);
    bool MatchRecipe(int i, int j, int recipe_row, int recipe_col, Recipes recipe);

    void Exporting(string file_name);
};