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
    int i;
    map<string, Item> item_map;
    string config_path = "./config";
    string item_config_path = config_path + "/item.txt";
    string array_line[4];
    // read item from config file
    ifstream item_config_file(item_config_path);
    for (string line; getline(item_config_file, line);) {
        i = 0;
        for (auto it = line.begin(); it != line.end(); it++) {
            if (*it != ' ') {
                array_line[i] += *it;
            } else {
                i++;
            }
        }
        if (array_line[3] == "NONTOOL") {
            item_map[array_line[1]] = NonTool(stoi(array_line[0]), array_line[1], array_line[2], NULL);
        } else {
            item_map[array_line[1]] = NonTool(stoi(array_line[0]), array_line[1], array_line[2], NULL);
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
