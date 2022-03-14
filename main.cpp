// sample main file, replace this with your own code
#include "Item.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    map<string, Item> inventory;
    map<string, Item> crafting;
    map<string, Item> item_map;
    string config_path = "./config";
    string item_config_path = config_path + "/item.txt";

    ifstream item_config_file(item_config_path);
    string line[4];
    for (string lines; getline(item_config_file, lines);) {
        int i = 0;
        string temp;
        for (auto it = lines.begin(); it != lines.end(); it++) {
            if (*it != ' ' - 1) {
                temp += *it;
            } else {
                line[i++] = temp;
                temp = "";
            }
        }
        line[i] = temp;
        if (line[3] == "TOOL") {
            item_map[line[1]] = Tool(stoi(line[0]), line[1], line[2], stoi(line[3]));
        } else {
            item_map[line[1]] = NonTool(stoi(line[0]), line[1], line[2], stoi(line[3]));
        }
    }

    // read recipes
    for (const auto &entry :
        filesystem::directory_iterator(config_path + "/recipe")) {
        cout << entry.path() << endl;
        // read from file and do something
    }

    // sample interaction
    string command;
    while (cin >> command) {
        if (command == "EXPORT") {
            string output_path;
            cin >> output_path;
            ofstream output_file(output_path);

            // hardcode for first test case
            output_file << "21:10" << endl;
            output_file << "6:1" << endl;
            for (int i = 2; i < 27; i++) {
                output_file << "0:0" << endl;
            }

            cout << "Exported" << endl;
        } else if (command == "CRAFT") {
            cout << "TODO" << endl;
        } else if (command == "GIVE") {
            string item_name;
            int item_qty;
            cin >> item_name >> item_qty;
            cout << "TODO" << endl;
        } else if (command == "MOVE") {
            string slot_src;
            int slot_qty;
            string slot_dest;
            // need to handle multiple destinations
            cin >> slot_src >> slot_qty >> slot_dest;
            cout << "TODO" << endl;
        } else {
            // todo
            cout << "Invalid command" << endl;
        }
    }
    return 0;
}
