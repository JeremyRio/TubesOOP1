#include "Recipes.hpp"

Recipes::Recipes() {
    this->row = 0;
    this->col = 0;
    this->make = new string[0];
    this->name = "none";
    this->craft_quantity = 0;
}
Recipes::Recipes(int row, int col, string name, int craft_quantity) {
    this->row = row;
    this->col = col;
    this->make = new string[row * col];
    this->name = name;
    this->craft_quantity = craft_quantity;
    this->neff = 0;
}

Recipes::Recipes(Recipes& other) : neff(0), row(other.row), col(other.col), name(other.name), craft_quantity(other.craft_quantity) {
    this->make = new string[row * col];
    for (int i = 0; i < other.neff; i++) {
        this->make[i] = other.make[i];
        this->neff++;
    }
}

Recipes::~Recipes() {
    delete[] this->make;
}

Recipes& Recipes::operator=(const Recipes& other) {
    delete[] make;  // bebaskan memory yang digunakan sebelumnya
    this->row = other.row;
    this->col = other.col;
    this->name = other.name;
    this->craft_quantity = other.craft_quantity;
    this->neff = 0;
    this->make = new string[row * col];
    for (int i = 0; i < other.neff; i++) {
        this->make[i] = other.make[i];
        this->neff++;
    }
    return *this;
}

void Recipes::print_info() {
    cout << "[";
    for (int i = 0; i < neff; i++) {
        cout << this->make[i];
        if (i != neff - 1) {
            cout << ",";
        }
    }
    cout << "]";
}

int Recipes::getrow(){
    return this->row;
}

int Recipes::getcol(){
    return this->col;
}

int Recipes::getCraftQuantity(){
    return this->craft_quantity;
}

int Recipes::getneff(){
    return this->neff;
}

string Recipes::GetRecipeIngredients(int idx) const{
    return this->make[idx];
}

Recipes& Recipes::operator<<(string bahan) {
    this->make[this->neff] = bahan;
    this->neff += 1;
    return *this;
}

Recipes& Recipes::Mirrored_Y_Recipe(){
    string temp;
    if (!getcol() == 1){
        int switchidx = getcol()-1;
        for (int i = 0; i < 3*getcol(); i++) {
            // swapping elements
            temp = this->make[i];
            this->make[i] = this->make[i+switchidx];
            this->make[i+switchidx] = temp;

        }
    }
    return *this;
}