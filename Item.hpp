#ifndef ITEM_HPP
#define ITEM_HPP

#define MAX_QTY 64
#define MAX_DURABILITY 10

#include <string>
using namespace std;

class Item {
    protected:
        int id;
        string name;
        string type;
        int quantity;

    public:
        Item(); 
        Item(int id, string name, string type, int quantity);

        int get_id();
        string get_name();
        string get_type();
        int get_quantity();

        void set_id(int id);
        void set_name(string name);
        void set_type(string type);
        void set_quantity(int quantity);

        void add_quantity(int quantity);
        void remove_quantity(int quantity);

};
class Tool : public Item {
    public:
        Tool();
        Tool(int id, string name, string type, int quantity);

};
class NonTool : public Item {
    private:
        int durability;
    public:
        NonTool();
        NonTool(int id, string name, string type, int durability);

        int get_durability();

        void set_durability(int durability);

        void add_durability(int durability);
        void remove_durability(int durability);

};

#endif