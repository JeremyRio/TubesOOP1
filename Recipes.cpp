#include "Recipes.hpp"

Recipes::Recipes(){
    this->row = 0;
    this->col = 0;
    this->make = new string[0];
    this->name = "none";
    this->craft_quantity = 0;
}
Recipes::Recipes(int row, int col, string name, int craft_quantity){
    this->row = row;
    this->col = col;
    this->make = new string[row*col];
    this->name = name;
    this->craft_quantity = craft_quantity;
    this->neff = 0;
}
Recipes::~Recipes() {
  delete[] this->make;
}
void Recipes::print_info(){
    cout << "[";
    for (int i = 0; i < neff; i++){
        cout << this->make[i];
        if (i != neff-1){
            cout << ",";
        }
    }
    cout << "]";
}
Recipes& Recipes::operator<<(string bahan){
    this->make[this->neff] = bahan;
    this->neff +=1;
    return *this;
}