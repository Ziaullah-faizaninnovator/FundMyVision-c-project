#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void suggestInvestmentAmount(int budget) {
    cout << "Suggestion: ";
    if (budget < 50000)
        cout << "Small trading business.\n";
    else if (budget < 200000)
        cout << "Food cart or delivery service.\n";
    else
        cout << "App development or online store.\n";
}

void registerInnovator() {
    string name, idea;
    cin.ignore();
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Describe your idea: ";
    getline(cin, idea);

    ofstream out("innovators.txt", ios::app);
    out << name << "," << idea << "\n";
    out.close();

    cout << "Innovator registered and idea saved!\n";
}

void registerInvestor() {
    string name;
    int budget;
    cin.ignore();
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your budget (Rs): ";
    cin >> budget;

    suggestInvestmentAmount(budget);

    ofstream out("investors.txt", ios::app);
    out << name << "," << budget << "\n";
    out.close();

    cout << "Investor registered and saved!\n";
}

void viewInnovators() {
    ifstream in("innovators.txt");
    string line;
    cout << "\n--- Innovators ---\n";
    while (getline(in, line)) {
        cout << line << "\n";
    }
    in.close();
}

void viewInvestors() {
    ifstream in("investors.txt");
    string line;
    cout << "\n--- Investors ---\n";
    while (getline(in, line)) {
        cout << line << "\n";
    }
    in.close();
}

void searchIdeas() {
    string keyword;
    cin.ignore();
    cout << "Enter keyword to search in ideas: ";
    getline(cin, keyword);

    ifstream in("innovators.txt");
    string line;
    bool found = false;
    while (getline(in, line)) {
        if (line.find(keyword) != string::npos) {
            cout << line << "\n";
            found = true;
        }
    }
    in.close();

    if (!found) {
        cout << "No matching ideas found.\n";
    }
}

void matchInvestorInnovator() {
    cout << "\nMatching all investors with all innovators:\n";
    viewInvestors();
    viewInnovators();
    cout << "You can suggest connections manually based on ideas and budgets.\n";
}

int main() {
    while (true) {
        cout << "\n===== FundMyVision =====\n";
        cout << "1. Register as Innovator\n";
        cout << "2. Register as Investor\n";
        cout << "3. View all Innovators\n";
        cout << "4. View all Investors\n";
        cout << "5. Search Ideas\n";
        cout << "6. Match Investor with Innovator\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1)
            registerInnovator();
        else if (choice == 2)
            registerInvestor();
        else if (choice == 3)
            viewInnovators();
        else if (choice == 4)
            viewInvestors();
        else if (choice == 5)
            searchIdeas();
        else if (choice == 6)
            matchInvestorInnovator();
        else if (choice == 7) {
            cout << "Thank you for using FundMyVision!\n";
            break;
        } else
            cout << "Invalid choice. Try again.\n";
    }
    return 0;
}
