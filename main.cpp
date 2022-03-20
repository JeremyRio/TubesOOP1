// sample main file, replace this with your own code

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "class/Item.hpp"
#include "class/NonTool.hpp"
#include "class/Recipes.hpp"
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
    map<string, Recipes*> recipe_map;
    for (const auto& filerecipe : filesystem::directory_iterator(recipe_config_path)) {
        ifstream recipe_config_file(filerecipe.path());
        string tempr;
        int cnt = 0;
        int sum = 1;
        string contain_recipes[14];
        for (string recipe_lines; getline(recipe_config_file, recipe_lines);) {
            // Traverse the string
            for (auto& ch : recipe_lines) {
                if (ch == ' ') {
                    contain_recipes[cnt] = tempr;
                    tempr = "";
                    cnt++;
                } else
                    tempr += ch;
            }
            contain_recipes[cnt] = tempr;
            tempr = "";
            cnt++;
        }
        int size = stoi(contain_recipes[0]) * stoi(contain_recipes[1]);
        Recipes* r = new Recipes(stoi(contain_recipes[0]), stoi(contain_recipes[1]), contain_recipes[2 + size], stoi(contain_recipes[3 + size]));
        for (int i = 2; i < 2 + size; i++) {
            (*r) << contain_recipes[i];
        }
        recipe_map[contain_recipes[2 + size]] = r;
    }

    // checking if it works
    // for (auto it1 = recipe_map.begin(); it1 != recipe_map.end(); ++it1) {
    //     it1->second->print_info();
    //     cout << it1->first << endl;
    // }

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
        } else if (command == "GIVE") {
            string item_name;
            int item_qty;
            cin >> item_name >> item_qty;
            inventory.Give(item_name, item_qty, item_map);
        } else if (command == "MOVE") {
            string slot_src;
            int slot_qty;
            string slot_dest;
            // need to handle multiple destinations
            cin >> slot_src >> slot_qty >> slot_dest;

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
