class Inventory {
    private:
    Item** items;

    public:
    Inventory() {
        items = new Item*[27];
        for (int i = 0; i < 27; i++) {
            items[i] = new Item();
        }
    }

    void Add(int idx, Item* item) {
        if (items[idx]->get_quantity() == 0) {
            delete items[idx];
            if (item->get_tool()) {
                items[idx] = new Tool(*(Tool*)item);
            } else {
                items[idx] = new NonTool(*(NonTool*)item);
            }
        } else {
            // Stack atau Swap item
        }
    }

    Item& operator[](int idx) {
        return *items[idx];
    }

    void Display() {
        for (int i = 0; i < 27; i++) {
            cout << "[ ";
            if (items[i]->get_quantity() > 0) {
                cout << items[i]->get_name() << " (" << items[i]->get_quantity() << ")";
            } else {
                cout << "EMPTY";
            }
            cout << " ]";
            if (i == 8 || i == 17) {
                cout << endl;
            } else {
                cout << " ";
            }
        }
    }
};