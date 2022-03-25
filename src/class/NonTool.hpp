#ifndef NONTOOL_HPP
#define NONTOOL_HPP

#include "Item.hpp"
#include "BaseException.hpp"

class NonTool : public Item {
    public:
    NonTool();
    NonTool(int id, string name, string type, int quantity);
    NonTool(const NonTool &t);
    NonTool(const Item &item);
    NonTool &operator=(const NonTool &t);
    void Stack(Item item_source, int quantity, Item item_destination);
    void Use();
    void DisplayInfo();  // check info item aja (dihapusin aja)
    void DisplayItem();
};

#endif