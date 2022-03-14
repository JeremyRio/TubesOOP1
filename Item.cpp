#include "Item.hpp"

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

int Item::get_id(){
    return this->id;
}
string Item::get_name(){
    return this->name;
}
string Item::get_type(){
    return this->type;
}
int Item::get_quantity(){
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

Tool::Tool() : Item(){
    
}
Tool::Tool(int id, string name, string type, int quantity) : Item(id, name, type, quantity){

}

void Tool::Stack(Item item_source, int quantity, Item item_destination){
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

NonTool::NonTool() : Item(){

}
NonTool::NonTool(int id, string name, string type, int durability) : Item(id, name, type, 1){
    this->durability = durability;
}

int NonTool::get_durability(){
    return this->durability;
}

void NonTool::set_durability(int durability){
    this->durability = durability;
}

void NonTool::add_durability(int durability){
    this->set_durability((10, this->get_durability()+durability));
}
void NonTool::remove_durability(int durability){
    this->set_durability(max(0, this->get_durability()-durability));
}