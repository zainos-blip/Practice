#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
using namespace std;

const int MAX_USERS = 25;

class Users {
private:
    string arrusername[MAX_USERS];
    string arrpassword[MAX_USERS];
    string arremail[MAX_USERS];
    int count = 0;

public:
    void registration(const string& username, const string& password, const string& email) {
        if (count < MAX_USERS) {
            arrusername[count] = username;
            arrpassword[count] = password;
            arremail[count] = email;
            count++;

            cout << "User registered successfully!" << endl;
        }
        else {
            cout << "Maximum user count reached. Cannot register more users." << endl;
        }
    }

    int getCount() const {
        return count;
    }

    string getUsername(int index) const {
        if (index >= 0 && index < count) {
            return arrusername[index];
        }
        return "";
    }

    string getPassword(int index) const {
        if (index >= 0 && index < count) {
            return arrpassword[index];
        }
        return "";
    }

    string getEmail(int index) const {
        if (index >= 0 && index < count) {
            return arremail[index];
        }
        return "";
    }

    void printRegisteredUsers() const {
        cout << "Registered Users: " << endl;
        for (int i = 0; i < count; i++) {
            cout << "Username: " << arrusername[i] << ", Password: " << arrpassword[i] << " Email: " << arremail[i] << endl;
        }
    }
};

class UserAuthentication {
private:
    Users users;
    Users* loggedInUser = nullptr;
    string loggedInUsername;

public:

    ~UserAuthentication() {
        saveUserData();
    }

    string getLoggedInUsername() const {
        return loggedInUsername;
    }

    bool login(const string& username, const string& password) {
        for (int i = 0; i < users.getCount(); i++) {
            if (users.getUsername(i) == username && users.getPassword(i) == password) {
                loggedInUser = &users;
                loggedInUsername = username;
                cout << "Login successful. Welcome, " << username << endl;
                return true;
            }
        }
        cout << "Login Failed, invalid username or password" << endl;
        return false;
    }

    void LogOut() {
        if (loggedInUser == &users) {
            loggedInUser = nullptr;
            cout << "Logged out." << endl;
        }
        else if (loggedInUser == nullptr) {
            cout << "User was never logged in." << endl;
        }
    }

    bool isLoggedIn() const {
        return loggedInUser != nullptr;
    }

    void registration(const string& username, const string& password, const string& email) {
        users.registration(username, password, email);
    }

    void printRegisteredUsers() const {
        users.printRegisteredUsers();
    }

    void loadUserData() {
        ifstream inFile("userdata.txt");

        if (!inFile) {
            cout << "Error opening file for reading." << endl;
            return;
        }

        string username, password, email;

        while (inFile >> username >> password >> email) {
            users.registration(username, password, email);
        }

        inFile.close();
    }

    void saveUserData() {
        ofstream outFile("userdata.txt");

        if (!outFile) {
            cout << "Error opening file for writing." << endl;
            return;
        }

        for (int i = 0; i < users.getCount(); i++) {
            outFile << users.getUsername(i) << " " << users.getPassword(i) << " " << users.getEmail(i) << endl;
        }

        outFile.close();
    }

};

class Item {
private:
    string name;
    string description;
    double price;
    bool availability = true;

public:
    Item() {}
    Item(const string& n, const string& d, double p) : name(n), description(d), price(p) {}

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    bool isAvailable() const {
        return availability;
    }
};

class ShoppingCart {
private:
    static const int SIZE = 10;
    Item cartItems[SIZE];
    int itemCount = 0;

public:
    void addToCart(const Item& item) {
        if (itemCount < SIZE) {
            cartItems[itemCount] = item;
            itemCount++;
            cout << "Item added to the shopping cart" << endl;

        }
        else {
            cout << "Maximum cart capacity reached. Cannot add more items" << endl;
        }
    }

    void showCartItems() const {
        for (int i = 0; i < itemCount; i++) {
            cout << "Item #" << i + 1 << ": " << cartItems[i].getName() << " - $" << cartItems[i].getPrice() << endl;
        }
    }

    void Bill() const {
        double totalbill = 0.0;
        for (int i = 0; i < itemCount; i++) {

            cout << "Item #" << i + 1 << ": " << cartItems[i].getName() << " - $" << cartItems[i].getPrice() << endl;
            totalbill += cartItems[i].getPrice();
        }
        cout << "TOTAL BILL: " << totalbill << endl;
    }

    void saveReceipt(const string& username) const {
        ofstream outFile("receipt_" + username + ".txt");

        if (!outFile) {
            cout << "Error opening file for writing." << endl;
            return;
        }

        outFile << "Receipt for user: " << username << endl;
        for (int i = 0; i < itemCount; i++) {
            outFile << "Item #" << i + 1 << ": " << cartItems[i].getName() << " - $" << cartItems[i].getPrice() << endl;
        }

        double totalbill = 0.0;
        for (int i = 0; i < itemCount; i++) {
            totalbill += cartItems[i].getPrice();
        }
        outFile << "TOTAL BILL: $" << totalbill << endl;

        outFile.close();
        cout << "Receipt saved." << endl;
    }
};

class MarketPlace {
private:
    static const int SIZE = 10;
    Item items[SIZE];
    int itemCount = 0;

public:
    void HardCodeaddItem(const string& name, const string& description, double price) {
        if (itemCount < SIZE) {
            items[itemCount] = Item(name, description, price);
            itemCount++;
        }
    }

    void addItem(const string& name, const string& description, double price) {
        if (itemCount < SIZE) {
            items[itemCount] = Item(name, description, price);
            itemCount++;
            cout << "Item added to marketplace" << endl;
        }
        else {
            cout << "Maximum item count reached. Cannot add more items" << endl;
        }
    }

    void showAvailableItems() const {
        cout << "Available items in the marketplace: " << endl;
        for (int i = 0; i < itemCount; i++) {
            if (items[i].isAvailable()) {
                cout << "Item #" << i + 1 << ": " << items[i].getName() << " - $" << items[i].getPrice() << endl;
            }
        }
    }
    void removeItem(int index) {
        if (index >= 0 && index < itemCount) {
            items[index] = items[itemCount - 1];
            itemCount--;
            cout << "Item removed from marketplace." << endl;
        }
    }

    int getItemCount() const {
        return itemCount;
    }

    const Item& getItem(int index) const {
        if (index >= 0 && index < itemCount) {
            return items[index];
        }
        // Return a default item or throw an exception if needed
    }
};

void SetStdinEcho(bool enable = true) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    if (!enable)
        mode &= ~ENABLE_ECHO_INPUT;
    else
        mode |= ENABLE_ECHO_INPUT;

    SetConsoleMode(hStdin, mode);
}

int main() {
    UserAuthentication auth;
    MarketPlace marketplace, mp, * ptrmp = nullptr;
    ShoppingCart cart, k, * ptrk = nullptr;

    double price;

    mp.HardCodeaddItem("Laptop", "High-performance laptop", 999.99);
    mp.HardCodeaddItem("Smartphone", "Latest smartphone model", 699.99);
    mp.HardCodeaddItem("Headphones", "Noise-cancelling headphones", 149.99);
    mp.HardCodeaddItem("Camera", "Professional DSLR camera", 1299.99);
    mp.HardCodeaddItem("Tablet", "Touchscreen tablet", 299.99);


    cout << "--------------ONLINE MARKETPLACE SIMULATION---------------" << endl;
    cout << "---------- BY ZAIN RASHID AND RIAZ AHMED ANSARI-----------------" << endl << endl;

    while (true) {
        cout << "\n\n1. REGISTRATION" << endl;
        cout << "2. LOGIN" << endl;
        cout << "3. LOGOUT" << endl;
        cout << "4. MARKETPLACE" << endl;
        cout << "5. DISPLAYING ITEMS AVAILABLE IN MARKETPLACE" << endl;
        cout << "6. SHOPPING CART" << endl;
        cout << "7. RECIEPT LIST" << endl;
        cout << "8. EXIT" << endl;

        cout << "SELECT THE OPTION YOU WANT: ";
        string input;
        cin >> input;

        if (input == "1") {
            string rusername, rpassword, remail;
            char ch;
            cout << "Enter username (no spaces): ";
            cin >> rusername;

            cout << "Enter password (no spaces): ";
            SetStdinEcho(false); // Disable input echoing
            cin >> rpassword;
            SetStdinEcho(true);  // Re-enable input echoing

            cout << endl;
            cout << "Enter the email: ";
            cin >> remail;

            auth.registration(rusername, rpassword, remail);
            auth.printRegisteredUsers();


            auth.saveUserData();
        }
        else if (input == "2") {
            string lusername, lpassword;

            cout << "Enter username: ";
            cin >> lusername;

            cout << "Enter password: ";
            SetStdinEcho(false); // Disable input echoing
            cin >> lpassword;
            SetStdinEcho(true);  // Re-enable input echoing

            if (auth.login(lusername, lpassword)) {
                cout << "User is logged in: " << auth.isLoggedIn() << endl;

                ptrmp = &mp;
                ptrk = &k;
            }
        }
        else if (input == "3") {
            auth.LogOut();
            cout << "User is logged in: " << auth.isLoggedIn() << endl;

            auth.saveUserData();

            ptrmp = nullptr;
            ptrk = nullptr;
        }
        else if (input == "4") {
            string name, description;
            bool condition = true;
            while (condition) {
                string option;

                cout << "1. ADD ITEMS, 2. LEAVE" << endl;
                cout << "SELECT OPTION YOU WANT: " << endl;
                cin >> option;

                if (option == "1") {
                    cout << "ADD YOUR ITEMS IN THE MARKETPLACE: " << endl;
                    cout << "Enter name of the item: ";
                    cin.ignore();
                    getline(cin, name);

                    cout << "Enter description of the item: ";
                    getline(cin, description);

                    cout << "Enter price of the item: ";
                    cin >> price;

                    ptrmp->addItem(name, description, price);
                }
                else if (option == "2") {
                    break;
                }
            }
        }


        else if (input == "5") {
            if (ptrmp == nullptr) {
                cout << "Log in first." << endl;
            }

            if (ptrmp != nullptr) {
                string condition;
                cout << "Want to display available items (enter true or false): ";
                cin >> condition;
                if (condition == "true" || condition == "1") {
                    ptrmp->showAvailableItems();
                }
                else {
                    cout << "Not displaying available info on your request." << endl;
                }
            }
        }

        else if (input == "6") {
            string condition;
            cout << "ADD ITEMS TO YOUR SHOPPING CART: " << endl;
            if (ptrmp == nullptr) {
                cout << "Please log in your account first." << endl;
                break;
            }
            else {
                ptrmp->showAvailableItems();
            }

            while (true) {
                int option;
                cout << "\n\n1. Add to Cart, 2. Exit Cart" << endl;
                cout << "Enter option: ";
                cin >> option;

                if (option == 1) {

                    int itemChoice;
                    cout << "Enter the item number you want to add to the cart: ";
                    cin >> itemChoice;

                    if (itemChoice >= 1 && itemChoice <= ptrmp->getItemCount()) {
                        ptrk->addToCart(ptrmp->getItem(itemChoice - 1));
                        cout << "Items in your shopping cart:" << endl;
                        ptrk->showCartItems();

                        ptrmp->removeItem(itemChoice - 1);
                    }

                    else {
                        cout << "Invalid item number. Please choose a valid item." << endl;
                    }
                }

                else if (option == 2) {
                    break;
                }
            }
        }

        else if (input == "7") {
            if (ptrk == nullptr) {
                cout << "Log in first." << endl;
            }

            if (ptrk != nullptr) {
                cout << "The items you bought are: " << endl;
                ptrk->Bill();
                ptrk->saveReceipt(auth.getLoggedInUsername());
            }
        }

        else if (input == "8") {
            cout << "Do you want to exit the program? (true or false): ";
            cin >> input;
            if (input == "true") {
                break;
            }
            else {
                cout << "Did not exit the program." << endl;
            }
        }
        else {
            cout << "Invalid option, please choose again." << endl;
        }
        system("pause");
        system("cls");
    }

    return 0;
}