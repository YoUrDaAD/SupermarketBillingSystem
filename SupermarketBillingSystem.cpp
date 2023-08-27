#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

class Item {
public:
    string name;
    double price;
    int quantity;

    Item(const string& n, double p, int q) : name(n), price(p), quantity(q) {}
};

class BillingSystem {
private:
    vector<Item> items;

public:
    void addItem(const string& name, double price, int quantity) {
        items.push_back(Item(name, price, quantity));
    }

    void displayBill() {
        double totalAmount = 0.0;

        cout << "-----------------------------------------------------------" << endl;
        cout << setw(20) << left << "Item Name" << setw(10) << "Quantity" << setw(15) << "Price" << setw(15) << "Total" << endl;
        cout << "-----------------------------------------------------------" << endl;

        for (vector<Item>::iterator it = items.begin(); it != items.end(); ++it) {
            const Item& item = *it;
            double totalItemAmount = item.price * item.quantity;
            totalAmount += totalItemAmount;

            cout << setw(20) << left << item.name
                 << setw(10) << item.quantity
                 << setw(15) << fixed << setprecision(2) << item.price
                 << setw(15) << fixed << setprecision(2) << totalItemAmount << endl;
        }

        cout << "-----------------------------------------------------------" << endl;
        cout << setw(45) << "Total Amount: " << setw(15) << fixed << setprecision(2) << totalAmount << endl;
    }

    void saveToFile(const string& filename) {
        ofstream outFile(filename.c_str());  // C++98 doesn't support passing strings directly

        if (!outFile) {
            cout << "Error opening file for writing!" << endl;
            return;
        }

        for (vector<Item>::iterator it = items.begin(); it != items.end(); ++it) {
            const Item& item = *it;
            outFile << item.name << " " << item.price << " " << item.quantity << endl;
        }

        outFile.close();
    }

    void loadFromFile(const string& filename) {
        ifstream inFile(filename.c_str());  // C++98 doesn't support passing strings directly

        if (!inFile) {
            cout << "Error opening file for reading!" << endl;
            return;
        }

        items.clear();
        string name;
        double price;
        int quantity;

        while (inFile >> name >> price >> quantity) {
            items.push_back(Item(name, price, quantity));
        }

        inFile.close();
    }
};

int main() {
    BillingSystem billingSystem;
    billingSystem.loadFromFile("items.txt");

    int choice;
    do {
        cout << "1. Add Item" << endl;
        cout << "2. Display Bill" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                double price;
                int quantity;

                cout << "Enter item name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter item price: ";
                cin >> price;
                cout << "Enter item quantity: ";
                cin >> quantity;

                billingSystem.addItem(name, price, quantity);
                break;
            }
            case 2:
                billingSystem.displayBill();
                break;
            case 3:
                billingSystem.saveToFile("items.txt");
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
