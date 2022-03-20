#ifndef TOOL_HPP
#define TOOL_HPP

#include "Item.hpp"

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