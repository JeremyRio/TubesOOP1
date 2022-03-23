#include "Recipes.hpp"

Recipes::Recipes() {
    this->row = 0;
    this->col = 0;
    this->recipe_array = new string[0];
    this->name = "none";
    this->craft_quantity = 0;
}

Recipes::Recipes(int row, int col, string name, int craft_quantity) {
    this->row = row;
    this->col = col;
    this->recipe_array = new string[row * col];
    this->name = name;
    this->craft_quantity = craft_quantity;
}

Recipes::Recipes(const Recipes& r) {
    this->row = r.row;
    this->col = r.col;
    this->recipe_array = new string[row * col];
    this->name = r.name;
    this->craft_quantity = r.craft_quantity;
    for (int i = 0; i < row * col; i++) {
        this->recipe_array[i] = r.recipe_array[i];
    }
}

Recipes::~Recipes() {
    delete[] this->recipe_array;
}

Recipes& Recipes::operator=(const Recipes& other) {
    delete[] recipe_array;  // bebaskan memory yang digunakan sebelumnya
    this->row = other.row;
    this->col = other.col;
    this->name = other.name;
    this->craft_quantity = other.craft_quantity;
    this->recipe_array = new string[row * col];
    return *this;
}

int Recipes::GetRow() const {
    return this->row;
}

int Recipes::GetCol() const {
    return this->col;
}

int Recipes::GetCraftQuantity() const {
    return this->craft_quantity;
}

string Recipes::GetName() const {
    return this->name;
}

void Recipes::SetRecipeIngredient(int idx, string ingredient) {
    this->recipe_array[idx] = ingredient;
}

string& Recipes::operator[](int idx) {
    return this->recipe_array[idx];
}

Recipes& Recipes::Mirrored_Y_Recipe() {
    string temp;
    if (!GetCol() == 1) {
        int switchidx = GetCol() - 1;
        for (int i = 0; i < 3 * GetCol(); i++) {
            // swapping elements
            temp = this->recipe_array[i];
            this->recipe_array[i] = this->recipe_array[i + switchidx];
            this->recipe_array[i + switchidx] = temp;
        }
    }
    return *this;
}

void Recipes::DisplayInfo() {
    cout << "Recipe: " << this->name << endl;
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            cout << this->recipe_array[i * this->col + j] << " ";
        }
        cout << endl;
    }
    cout << GetCraftQuantity() << endl;
}