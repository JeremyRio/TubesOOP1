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

Recipes::Recipes(Recipes& other) : neff(0), row(other.row), col(other.col), name(other.name), craft_quantity(other.craft_quantity){
    this->make = new string[row*col];
    for (int i = 0; i < other.neff; i++) {
        this->make[i] = other.make[i];
        this->neff++;
    }
}

Recipes::~Recipes() {
  delete[] this->make;
}

Recipes& Recipes::operator=(const Recipes& other){
    delete[] make; // bebaskan memory yang digunakan sebelumnya
    this->row = other.row;
    this->col = other.row;
    this-> name = other.name;
    this->craft_quantity = other.craft_quantity;
    this->neff = 0;
    this->make = new string[row*col];
    for (int i = 0; i < other.neff; i++) {
        this->make[i] = other.make[i];
        this->neff++;
    }
    return *this;
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

bool Recipes::Matching(Inventory* item, Recipes* other){
    // checking the normal position
    if (sameItem(item)) {return true;}

    // checking in different positions
    Recipes *temp_recipe = new Recipes(*other);
    for (int i = 0; i < 2; i++){
        *temp_recipe = *other;
        
        // check mirrored position
        if (i == 1) { 
            (*temp_recipe).Mirrored_Y_Recipe();
            if (temp_recipe->sameItem(item)) {return true;}
        }

        // check right position
        (*temp_recipe).GeserKanan();
        if (temp_recipe->sameItem(item)) {return true;}

        //check left position 
        (*temp_recipe).GeserKiri().GeserKiri();
        if (temp_recipe->sameItem(item)) {return true;}
    }
    return false;
}

Recipes& Recipes::GeserKiri(){
    string temp;
    for (int i = 8; i > 0; i-= 3){
        string temp = this->make[i];
        string temp1 = this->make[i-1];
        this->make[i-1] = temp;
        this->make[i-2] = temp1;
        this->make[i] = "-";
    }
    return *this;
}

Recipes& Recipes::GeserKanan(){
    string temp;
    for (int i = 0; i < 9; i+= 3){
        string temp = this->make[i];
        string temp1 = this->make[i+1];
        this->make[i+1] = temp;
        this->make[i+2] = temp1;
        this->make[i] = "-";
    }
    return *this;
}

Recipes& Recipes::Mirrored_Y_Recipe(){
    string temp;
    for (int i = 0; i < 9; i+= 3){
        //swapping elements
        temp = this->make[i];
        this->make[i] = this->make[i+2];
        this->make[i+2] = temp;
    }
    return *this;
}