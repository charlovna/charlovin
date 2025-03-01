#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Product {
public:
    string id, name;
    double price;
    
    Product(string id, string name, double price) : id(id), name(name), price(price) {}
};

class ShoppingCart {
private:
    struct CartItem {
        Product product;
        int quantity;
        CartItem(Product p, int q) : product(p), quantity(q) {}
    };
    vector<CartItem> items;
public:
    void addProduct(Product p) {
        for (auto &item : items) {
            if (item.product.id == p.id) {
                item.quantity++;
                cout << "Product added successfully!" << endl;
                return;
            }
        }
        items.push_back(CartItem(p, 1));
        cout << "Product added successfully!" << endl;
    }
    
    void viewCart() {
        if (items.empty()) {
            cout << "Your shopping cart is empty!" << endl;
            return;
        }
        cout << "Shopping Cart:\n";
        cout << left << setw(12) << "Product ID" << setw(10) << "Name" << setw(10) << "Price" << "Quantity" << endl;
        for (const auto &item : items) {
            cout << left << setw(12) << item.product.id << setw(10) << item.product.name << setw(10) << item.product.price << item.quantity << endl;
        }
    }
    
    double checkout() {
        double total = 0;
        for (const auto &item : items) {
            total += item.product.price * item.quantity;
        }
        items.clear();
        return total;
    }
};

class Order {
public:
    int orderId;
    double totalAmount;
    vector<Product> products;
    vector<int> quantities;
    
    Order(int id, double amount, vector<Product> prods, vector<int> qtys) : orderId(id), totalAmount(amount), products(prods), quantities(qtys) {}
    
    void displayOrder() {
        cout << "\nOrder ID: " << orderId << endl;
        cout << "Total Amount: " << totalAmount << endl;
        cout << "Order Details:" << endl;
        cout << left << setw(12) << "Product ID" << setw(10) << "Name" << setw(10) << "Price" << "Quantity" << endl;
        for (size_t i = 0; i < products.size(); i++) {
            cout << left << setw(12) << products[i].id << setw(10) << products[i].name << setw(10) << products[i].price << quantities[i] << endl;
        }
    }
};

int main() {
    vector<Product> products = {
        Product("ABC", "Paper", 20),
        Product("CDE", "Pencil", 10),
        Product("QWE", "Paper", 20),
        Product("TRE", "Pencil", 10),
        Product("ASD", "Paper", 20),
        Product("ZXC", "Pencil", 10)
    };
    vector<Order> orders;
    ShoppingCart cart;
    int orderCounter = 1;
    char choice;
    
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. View Products\n2. View Shopping Cart\n3. View Orders\n4. Exit\nChoose an option: ";
        cin >> choice;
        
        if (choice == '1') {
            cout << "\nAvailable Products:\n";
            cout << left << setw(12) << "Product ID" << setw(10) << "Name" << "Price" << endl;
            for (const auto &p : products) {
                cout << left << setw(12) << p.id << setw(10) << p.name << p.price << endl;
            }
            
            while (true) {
                string pid;
                cout << "Enter the ID of the product to add (or '0' to return to menu): ";
                cin >> pid;
                if (pid == "0") break;
                bool found = false;
                for (const auto &p : products) {
                    if (p.id == pid) {
                        cart.addProduct(p);
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Invalid Product ID!" << endl;
            }
        } 
        else if (choice == '2') {
            cart.viewCart();
            cout << "Do you want to checkout? (Y/N): ";
            char confirm;
            cin >> confirm;
            if (confirm == 'Y' || confirm == 'y') {
                double total = cart.checkout();
                cout << "You have successfully checked out! Total: " << total << endl;
                orders.push_back(Order(orderCounter++, total, {}, {}));
            }
        } 
        else if (choice == '3') {
            if (orders.empty()) {
                cout << "No orders found." << endl;
            } else {
                for (auto &order : orders) {
                    order.displayOrder();
                }
            }
        } 
        else if (choice == '4') {
            break;
        } 
        else {
            cout << "Invalid choice! Plz Try again." << endl;
        }
    }
    return 0;
}
