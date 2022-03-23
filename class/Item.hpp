#ifndef ITEM_HPP
#define ITEM_HPP

#define MAX_QTY 64
#define MAX_DURABILITY 10

#include "BaseException.hpp"

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
    int GetID() const;
    string GetName() const;
    string GetType() const;
    int GetQuantity() const;

    void SetID(int id);
    void SetName(string name);
    void SetType(string type);
    void SetQuantity(int quantity);
    void AddQuantity(int quantity);
    void RemoveQuantity(int quantity);
    virtual void Use();
    virtual void DisplayInfo();
    virtual void DisplayItem();
    virtual int GetDurability() const;
    virtual void SetDurability(int durability);
};

#endif