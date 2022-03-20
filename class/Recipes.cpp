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

Recipes& Recipes::NormalPosition(Recipes& r){
    *this = Recipes(3, 3, r.name, r.craft_quantity);
    if (r.col == 1){
        this->FillEmpty();
        int temp = 1;
        for (int i = 1; i < 8; i+=3){
            this->make[i] = r.make[i-temp];
            temp+=2;
        }
        this->neff = 9;
        return *this;
    }
    else{
        *this = r;
        return *this;
    }
}
    
Recipes& Recipes::GeserKiri(Recipes& r){
    // cout << r.getcol() << "berapa rownya" << endl << endl;
    int temp = 0;
    //Recipes *rnew = new Recipes(3, 3, r.name, r.craft_quantity);
    *this =  Recipes(3, 3, r.name, r.craft_quantity);
    this->FillEmpty();
    if (r.col == 2){
        for (int i = 0; i < 9; i++){
        if ((i+1)%(r.row) == 0){temp++;}
        else this->make[i] = r.make[i-temp];
        }
        this->neff = 9;
        return *this;
    }
    else if (r.col == 1){
        for (int i = 0; i < 9; i+= 3){
            this->make[i] = r.make[i-temp];
            temp+=2;
        }
        this->neff = 9;
        return *this;
    }
    else {
        *this = r;
        return *this;
    }
}

Recipes& Recipes::GeserKanan(Recipes& r){
    int temp = 0;
    //Recipes *rnew = new Recipes(3, 3, r.name, r.craft_quantity);
    *this =  Recipes(3, 3, r.name, r.craft_quantity);
    this->FillEmpty();
    if (r.col == 2){
        for (int i = 0; i < 9; i++){
            if ((i)%(r.row) == 0){temp++;}
            else this->make[i] = r.make[i-temp];
        }
        this->neff = 9;
        return *this;
    }
    else if (r.col == 1){
        temp = 2;
        for (int i = 2; i < 9; i+= 3){
            this->make[i] = r.make[i-temp];
            temp+=2;
        }
        this->neff = 9;
        return *this;
    }
    else {
        *this = r;
        return *this;
    }
}

Recipes& Recipes::Mirrored_Y_Recipe(){
    string temp;
    if (this->col == 2){
        for (int i = 0; i < 6; i+= 2){
        //swapping elements
            temp = this->make[i];
            this->make[i] = this->make[i+1];
            this->make[i+1] = temp;
        }
    }
    return *this;
}

Recipes& Recipes::FillEmpty(){
    string temp;
    for (int i = 0; i < 9; i++){
        this->make[i] = "-";
    }
    return *this;
}