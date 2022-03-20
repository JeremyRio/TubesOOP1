#ifndef RECIPES_HPP
#define RECIPES_HPP
#include <iostream>
using namespace std;

class Recipes{
private:
    string* make;
    int row;
    int col;
    string name;
    int craft_quantity;
    int neff;

public:
    //ctor default
    Recipes();
    //ctor
    Recipes(int row, int col, string name, int craft_quantity);
    //cctor
    Recipes(Recipes& other);
    //dtor
    ~Recipes();
    //operator=
    Recipes& operator=(const Recipes& other);
    //methods
    void print_info();
    int getneff();
    int getrow();
    int getcol();
    string GetRecipeIngredients(int idx) const;
    int getCraftQuantity();
    //menambahkan elemen ke dalam array make
    Recipes& operator<<(string bahan);

    //manipulasi recipes
    Recipes& NormalPosition(Recipes& r);

    Recipes& GeserKiri(Recipes& r);

    Recipes& GeserKanan(Recipes& r);

    Recipes& Mirrored_Y_Recipe();

    Recipes& FillEmpty();
};

#endif