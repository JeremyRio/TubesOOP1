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
    //dtor
    ~Recipes();
    //methods
    void print_info();
    //menambahkan elemen ke dalam array make
    Recipes& operator<<(string bahan);

};

#endif