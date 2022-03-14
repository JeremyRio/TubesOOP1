#include "Item.hpp"
#include <iostream>
Item::Item(){
    this->id = 0;
    this->name = "-";
    this->type = "-";
    this->quantity = 1;
}
Item::Item(int id, string name, string type, int quantity){
    this->id = id;
    this->name = name;
    this->type = type;
    this->quantity = quantity;
}

Item::Item(const Item& t){
    this->id = t.id;
    this->name = t.name;
    this->quantity = t.quantity;
    this->type = t.type; 
}

int Item::get_id() const{
    return this->id;
}
string Item::get_name() const{
    return this->name;
}
string Item::get_type() const{
    return this->type;
}
int Item::get_quantity() const{
    return this->quantity;
}

void Item::set_id(int id){
    this->id = id;
}
void Item::set_name(string name){
    this->name = name;
}
void Item::set_type(string type){
    this->type = type;
}
void Item::set_quantity(int quantity){
    this->quantity = quantity;
}

void Item::add_quantity(int quantity){
    // Implementasi Exception Handling
    this->set_quantity(this->get_quantity()+quantity);
}
void Item::remove_quantity(int quantity){
    // Implementasi Exception Handling
    this->set_quantity(this->get_quantity()-quantity);
}
void Item::display_info(){
    //easier checking
    cout << "id: " << get_id() << "\n";
    cout << "Name: " << get_name() << "\n";
    cout << "Type: " << get_type() << "\n";
    cout << "Quantity: " << get_quantity() << "\n";
}
NonTool::NonTool() : Item(){
    
}
NonTool::NonTool(int id, string name, string type, int quantity) : Item(id, name, type, quantity){

}

NonTool::NonTool(const NonTool& t) : Item(t){

}

void NonTool::Stack(Item item_source, int quantity, Item item_destination){
    if (item_source.get_id()!=item_destination.get_id()){
        // Implementasi Exception Handling
    } else {
        if (item_source.get_quantity()<=quantity){
            int temp = quantity + item_destination.get_quantity();
            if (temp > 64){
                item_destination.set_quantity(64);
                item_source.set_quantity(item_source.get_quantity()-quantity+temp-64);
            } else {
                item_destination.set_quantity(item_destination.get_quantity()+quantity);
                item_source.set_quantity(item_source.get_quantity()-quantity);
            }
        } else {
            // Implementasi Exception Handling
        }
    }
}
void NonTool::display_info(){
    //easier checking
    cout << "Item: " << "Non Tool"<< endl;
    Item::display_info();
}
Tool::Tool() : Item(){

}
Tool::Tool(int id, string name, string type, int durability) : Item(id, name, type, 1){
    this->durability = durability;
}

Tool::Tool(const Tool& t) : Item(t){
    this->durability = t.durability;
}
int Tool::get_durability() const{
    return this->durability;
}

void Tool::set_durability(int durability){
    this->durability = durability;
}

void Tool::add_durability(int durability){
    this->set_durability((10, this->get_durability()+durability));
}
void Tool::remove_durability(int durability){
    this->set_durability(max(0, this->get_durability()-durability));
}
void Tool::display_info(){
    cout << "Item: Tool" << endl;
    Item::display_info();
    cout << "Durability: " << get_durability() <<endl;
}