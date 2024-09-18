#include <iostream>
#include <string>

using namespace std; 

class Product {
public:
    string productId, name;
    double price;

    Product() {}
    Product(string id, string n, double p) : productId(id), name(n), price(p) {}
};

class ShoppingCart {
public:
    Product items[10];
    int quantities[10];
    int itemCount = 0;

    void addItem(Product product, int quantity) {
        items[itemCount] = product;
        quantities[itemCount] = quantity;
        itemCount++;
        cout << "Product added!\n";
    }

    void viewCart() {
        cout << "Product ID\tName\tPrice\tQuantity\n";
        for (int i = 0; i < itemCount; i++)
            cout << items[i].productId << "\t" << items[i].name << "\t" << items[i].price << "\t" << quantities[i] << endl;
    }

    double checkout() {
        double total = 0;
        for (int i = 0; i < itemCount; i++)
            total += items[i].price * quantities[i];
        return total;
    }

    void clearCart() {
        itemCount = 0;
    }
};

class Order {
public:
    int orderId;
    double totalAmount;
    Product orderDetails[10];
    int quantities[10];
    int itemCount;

    Order() {}
    Order(int id, double total, Product items[], int qtys[], int count) : orderId(id), totalAmount(total), itemCount(count) {
        for (int i = 0; i < count; i++) {
            orderDetails[i] = items[i];
            quantities[i] = qtys[i];
        }
    }

    void viewOrder() {
        cout << "Order ID: " << orderId << "\nTotal: " << totalAmount << "\nProduct ID\tName\tPrice\tQuantity\n";
        for (int i = 0; i < itemCount; i++)
            cout << orderDetails[i].productId << "\t" << orderDetails[i].name << "\t" << orderDetails[i].price << "\t" << quantities[i] << endl;
    }
};

int main() {
    Product products[3] = { Product("ABC", "Paper", 20), Product("CDE", "Pencil", 10), Product("QWE", "Notebook", 50) };
    ShoppingCart cart;
    Order orders[10];
    int orderCount = 0;
    int orderIdCounter = 1;
    char option;

    do {
        cout << "\n1. View Products\n2. View Cart\n3. Checkout\n4. View Orders\n5. Exit\nChoice: ";
        cin >> option;

        if (option == '1') { //view product
            cout << "Product ID\tName\tPrice\n";
            for (int i = 0; i < 3; i++)
                cout << products[i].productId << "\t" << products[i].name << "\t" << products[i].price << endl;

            string id;
            int qty;
            cout << "Enter Product ID: "; cin >> id;
            cout << "Enter quantity: "; cin >> qty;

            for (int i = 0; i < 3; i++) {
                if (products[i].productId == id)
                    cart.addItem(products[i], qty);
            }

        } else if (option == '2') {
            cart.viewCart();
        } else if (option == '3') {
            double total = cart.checkout();
            cout << "Total: " << total << "\nCheckout? (Y/N): ";
            char checkoutOpt; cin >> checkoutOpt;
            if (checkoutOpt == 'Y') {
                orders[orderCount] = Order(orderIdCounter++, total, cart.items, cart.quantities, cart.itemCount);
                orderCount++;
                cart.clearCart();
                cout << "Checked out!\n";
            }
        } else if (option == '4') {
            for (int i = 0; i < orderCount; i++)
                orders[i].viewOrder();
        }
    } while (option != '5');

    return 0;
}