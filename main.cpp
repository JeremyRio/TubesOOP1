// sample main file, replace this with your own code

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "class/Inventory.hpp"
#include "class/Item.hpp"
#include "class/NonTool.hpp"
#include "class/Tool.hpp"

using namespace std;

int main() {
    // read configuration file
    map<string, Item*> item_map;
    string config_path = "./config";
    string item_config_path = config_path + "/item.txt";
    string recipe_config_path = config_path + "/recipe";

    ifstream item_config_file(item_config_path);
    string line[4];
    for (string item_line; getline(item_config_file, item_line);) {
        int i = 0;
        string temp;
        for (auto& ch : item_line) {
            if (ch != ' ') {
                temp += ch;
            } else {
                line[i++] = temp;
                temp = "";
            }
        }
        line[3] = temp;
        if (line[3] == "TOOL") {
            item_map[line[1]] = new Tool(stoi(line[0]), line[1], line[2], 10);
        } else {
            item_map[line[1]] = new NonTool(stoi(line[0]), line[1], line[2], 0);
        }
    }

    // read recipes
    map<int, vector<Recipes>> recipe_map;
    for (const auto& filerecipe : filesystem::directory_iterator(recipe_config_path)) {
        ifstream recipe_config_file(filerecipe.path());
        string temp;
        string line[13];
        int i = 0;
        for (string recipe_lines; getline(recipe_config_file, recipe_lines);) {
            // Traverse the string
            for (auto& ch : recipe_lines) {
                if (ch != ' ') {
                    temp += ch;
                } else {
                    line[i++] = temp;
                    temp = "";
                }
            }
            line[i++] = temp;
            temp = "";
        }
        int row = stoi(line[0]);
        int col = stoi(line[1]);
        int size = row * col;
        Recipes recipe(row, col, line[2 + size], stoi(line[3 + size]));
        int count = 0;
        for (i = 0; i < size; i++) {
            if (line[2 + i] != "-") {
                count++;
            }
            recipe.SetRecipeIngredient(i, line[2 + i]);
        }
        // testing
        // recipe.DisplayInfo();
        //
        recipe_map[count].push_back(recipe);
    }

    // sample interaction
    string command;
    Inventory inventory;

    while (true) {
        cout << "\nInventory:\n";
        inventory.Show();
        cout << endl;
        cout << "COMMAND >>> ";
        cin >> command;
        if (command == "EXPORT") {
            string output_path;
            cin >> output_path;
            ofstream output_file(output_path);
        } else if (command == "CRAFT") {
            inventory.Crafting(recipe_map, item_map);
        } else if (command == "GIVE") {
            string item_name;
            int item_qty;
            cin >> item_name >> item_qty;
            inventory.Give(item_name, item_qty, item_map);
        } else if (command == "MOVE") {
            string slot_src;
            int slot_qty;
            string slot_dest;
            // still need to handle multiple destinations
            cin >> slot_src >> slot_qty;
            getline(cin, slot_dest);
            int idxSrc = (int)slot_src[1] - 48;
            if (slot_src[0] == 'C') idxSrc += 27;
            if (slot_src.length() > 2) idxSrc = idxSrc * 10 + (int)slot_src[2] - 48;
            int idxDest;
            string tempDest = "";
            int count = 1;
            // Menghitung jumlah slot yang dituju
            for (int i = 1; i < slot_dest.length(); i++) {
                if (slot_dest[i] == ' ') count++;
            }
            int amountPerStack = slot_qty / count;
            int remainder = slot_qty % count;
            // Membagi berdasarkan jumlah slot
            for (int i = 1; i < slot_dest.length(); i++) {
                if (slot_dest[i] == ' ' || i == slot_dest.length() - 1) {
                    if (i == slot_dest.length() - 1) tempDest += slot_dest[i];
                    idxDest = (int)tempDest[1] - 48;
                    if (tempDest[0] == 'C') idxDest += 27;
                    if (tempDest.length() > 2) idxDest = idxDest * 10 + (int)tempDest[2] - 48;
                    if (remainder > 0) {
                        inventory.Move(idxSrc, amountPerStack + 1, idxDest);
                        remainder--;
                    } else {
                        inventory.Move(idxSrc, amountPerStack, idxDest);
                    }
                    tempDest = "";
                    ;
                } else {
                    tempDest += slot_dest[i];
                }
            }
        } else if (command == "USE") {
            string inventory_id;
            cin >> inventory_id;
            inventory.Use(inventory_id);
        } else {
            // todo
            cout << "Invalid command" << endl;
        }
    }
    return 0;
}
