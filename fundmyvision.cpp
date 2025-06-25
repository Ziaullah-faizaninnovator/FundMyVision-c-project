// FundMyVision - Full Code with Login, Update, Delete (OOP Based)
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ---------------- Base User Class ----------------
class User {
protected:
    string name;
public:
    User(string name) : name(name) {}
    virtual void displayMenu() = 0;
};

// ---------------- Innovator Class ----------------
class Innovator : public User {
private:
    string idea;
    string password;

public:
    Innovator(string name, string idea, string password) : User(name), idea(idea), password(password) {}

    void saveToFile() {
        ofstream out("innovators.txt", ios::app);
        out << name << "," << idea << "," << password << "\n";
        out.close();
    }

    static bool login(string name, string pass) {
        ifstream in("innovators.txt");
        string line;
        while (getline(in, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.rfind(',');
            string uname = line.substr(0, pos1);
            string upass = line.substr(pos2 + 1);
            if (uname == name && upass == pass) {
                cout << "Login successful (Innovator).\n";
                return true;
            }
        }
        cout << "Login failed.\n";
        return false;
    }

    static void updateIdea(string name) {
        ifstream in("innovators.txt");
        ofstream out("temp.txt");
        string line;
        bool updated = false;
        cin.ignore();
        cout << "Enter new idea: ";
        string newIdea;
        getline(cin, newIdea);
        while (getline(in, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.rfind(',');
            string uname = line.substr(0, pos1);
            string upass = line.substr(pos2 + 1);
            if (uname == name) {
                out << uname << "," << newIdea << "," << upass << "\n";
                updated = true;
            } else {
                out << line << "\n";
            }
        }
        in.close(); out.close();
        remove("innovators.txt");
        rename("temp.txt", "innovators.txt");
        if (updated) cout << "Idea updated.\n";
        else cout << "User not found.\n";
    }

    static void deleteUser(string name) {
        ifstream in("innovators.txt");
        ofstream out("temp.txt");
        string line;
        bool deleted = false;
        while (getline(in, line)) {
            if (line.find(name + ",") != 0) {
                out << line << "\n";
            } else {
                deleted = true;
            }
        }
        in.close(); out.close();
        remove("innovators.txt");
        rename("temp.txt", "innovators.txt");
        if (deleted) cout << "Innovator deleted.\n";
        else cout << "User not found.\n";
    }

    void displayMenu() override {
        cout << "Welcome, Innovator: " << name << "\n";
    }
};

// ---------------- Investor Class ----------------
class Investor : public User {
private:
    int budget;
    string password;

public:
    Investor(string name, int budget, string password) : User(name), budget(budget), password(password) {}

    void saveToFile() {
        ofstream out("investors.txt", ios::app);
        out << name << "," << budget << "," << password << "\n";
        out.close();
    }

    static bool login(string name, string pass) {
        ifstream in("investors.txt");
        string line;
        while (getline(in, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.rfind(',');
            string uname = line.substr(0, pos1);
            string upass = line.substr(pos2 + 1);
            if (uname == name && upass == pass) {
                cout << "Login successful (Investor).\n";
                return true;
            }
        }
        cout << "Login failed.\n";
        return false;
    }

    static void deleteUser(string name) {
        ifstream in("investors.txt");
        ofstream out("temp.txt");
        string line;
        bool deleted = false;
        while (getline(in, line)) {
            if (line.find(name + ",") != 0) {
                out << line << "\n";
            } else {
                deleted = true;
            }
        }
        in.close(); out.close();
        remove("investors.txt");
        rename("temp.txt", "investors.txt");
        if (deleted) cout << "Investor deleted.\n";
        else cout << "User not found.\n";
    }

    void suggestInvestment() {
        cout << "Investment Suggestion: ";
        if (budget < 50000) cout << "Small trading business.\n";
        else if (budget < 200000) cout << "Food cart or delivery service.\n";
        else cout << "App development or online store.\n";
    }

    void displayMenu() override {
        cout << "Welcome, Investor: " << name << "\n";
        suggestInvestment();
    }
};

// ---------------- Main Menu ----------------
int main() {
    while (true) {
        cout << "\n===== FundMyVision Menu =====\n";
        cout << "1. Register Innovator\n2. Register Investor\n3. Login Innovator\n4. Login Investor\n";
        cout << "5. Update Idea\n6. Delete Innovator\n7. Delete Investor\n8. Exit\nEnter choice: ";
        int choice; cin >> choice;

        if (choice == 1) {
            string name, idea, pass;
            cin.ignore();
            cout << "Name: "; getline(cin, name);
            cout << "Idea: "; getline(cin, idea);
            cout << "Password: "; getline(cin, pass);
            Innovator(name, idea, pass).saveToFile();
            cout << "Innovator registered.\n";
        } else if (choice == 2) {
            string name, pass;
            int budget;
            cin.ignore();
            cout << "Name: "; getline(cin, name);
            cout << "Budget: "; cin >> budget;
            cin.ignore();
            cout << "Password: "; getline(cin, pass);
            Investor(name, budget, pass).saveToFile();
            cout << "Investor registered.\n";
        } else if (choice == 3) {
            string name, pass;
            cin.ignore();
            cout << "Name: "; getline(cin, name);
            cout << "Password: "; getline(cin, pass);
            Innovator::login(name, pass);
        } else if (choice == 4) {
            string name, pass;
            cin.ignore();
            cout << "Name: "; getline(cin, name);
            cout << "Password: "; getline(cin, pass);
            Investor::login(name, pass);
        } else if (choice == 5) {
            string name;
            cin.ignore();
            cout << "Enter Innovator Name: ";
            getline(cin, name);
            Innovator::updateIdea(name);
        } else if (choice == 6) {
            string name;
            cin.ignore();
            cout << "Enter Innovator Name to Delete: ";
            getline(cin, name);
            Innovator::deleteUser(name);
        } else if (choice == 7) {
            string name;
            cin.ignore();
            cout << "Enter Investor Name to Delete: ";
            getline(cin, name);
            Investor::deleteUser(name);
        } else if (choice == 8) {
            cout << "Thank you for using FundMyVision.\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}
