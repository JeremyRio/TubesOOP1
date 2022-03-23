#ifndef RECIPES_HPP
#define RECIPES_HPP
#include <iostream>
using namespace std;

class Recipes {
    private:
    string* recipe_array;
    int row;
    int col;
    int craft_quantity;
    string name;
    bool is_type;

    public:
    // ctor default
    Recipes();
    // ctor
    Recipes(int row, int col, string name, int craft_quantity);
    // cctor
    Recipes(const Recipes&);
    // dtor
    ~Recipes();
    // operator=
    Recipes& operator=(const Recipes& other);
    // methods
    void print_info();
    int GetNeff() const;
    int GetRow() const;
    int GetCol() const;
    int GetCraftQuantity() const;
    string GetName() const;
    void SetRecipeIngredient(int idx, string ingredient);
    void DisplayInfo();
    string& operator[](int idx);
};

#endif