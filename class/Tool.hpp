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
    int GetDurability() const;
    void Use();
    void SetDurability(int durability);
    void AddDurability(int durability);
    void RemoveDurability(int durability);
    void DisplayInfo();  // check info item aja (dihapusin aja)
    void DisplayItem();
    void RemoveQuantity(int quantity);
};

#endif