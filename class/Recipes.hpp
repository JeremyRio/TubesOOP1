#ifndef RECIPES_HPP
#define RECIPES_HPP
#include "Inventory.hpp"
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
    //menambahkan elemen ke dalam array make
    Recipes& operator<<(string bahan);

    //manipulasi recipes
    bool Matching(Inventory* item, Recipes* other);

    Recipes& GeserKiri();

    Recipes& GeserKanan();

    Recipes& Mirrored_Y_Recipe();

};

#endif