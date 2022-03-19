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
    Item(const Item &t);
    Item &operator=(const Item &t);
    int get_id() const;
    string get_name() const;
    string get_type() const;
    int get_quantity() const;

    void set_id(int id);
    void set_name(string name);
    void set_type(string type);
    void set_quantity(int quantity);

    void add_quantity(int quantity);
    void remove_quantity(int quantity);
    virtual void display_info();  // check info item aja (dihapusin aja)
    virtual void Use();
    virtual void DisplayItem();
};

class NonTool : public Item {
    public:
    NonTool();
    NonTool(int id, string name, string type, int quantity);
    NonTool(const NonTool &t);
    NonTool(const Item &item);
    NonTool &operator=(const NonTool &t);
    void Stack(Item item_source, int quantity, Item item_destination);
    void Use();
    void display_info();  // check info item aja (dihapusin aja)
    void DisplayItem();
};

class Tool : public Item {
    private:
    int durability;

    public:
    Tool();
    Tool(int id, string name, string type, int durability);
    Tool(const Tool &t);
    Tool &operator=(const Tool &t);
    int get_durability() const;
    void Use();
    void set_durability(int durability);
    void add_durability(int durability);
    void remove_durability(int durability);
    void display_info();  // check info item aja (dihapusin aja)
    void DisplayItem();
};

#endif