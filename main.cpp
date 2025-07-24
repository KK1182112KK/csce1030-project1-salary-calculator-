/* Author: Kenshin Kotari (KotariKenshin@unt.edu)
   EUID: kk1267
    Date:      06/26/2025
   Instructor: Amar Maharjan, Anamul Haque Mollah, Bailu Zhang
   Description: CSCE 1030 Project 1 - Salary Calculator
*/

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

enum Role { Manager, Developer, Tester, Intern };

int main() {
    
    srand(static_cast<unsigned>(time(nullptr)));

    const double BASE_SALARY[] = {5000.0, 4000.0, 3000.0, 1500.0};
    const double MAX_BONUS[]   = {300.0, 250.0, 200.0, 150.0};
    const double OT_RATE[]     = {25.0, 20.0, 15.0, 0.0};
    const double MIN_BONUS     = 100.0;

    int employeeCount = 0;
    char again = 'Y';

    while (toupper(again) == 'Y') {

        ++employeeCount;
        cout << "Calculating salary for Employee #" << employeeCount << endl;

        string name;

        while (true) {
            cout << "Enter employee name (alphabets and spaces only): ";
            getline(cin, name);
            bool valid = !name.empty();

            for (char c : name) {
                if (!isalpha(c) && c != ' ') {
                    valid = false;
                    break;
                }
            }
            if (valid) break;
            cout << "Invalid name! Use alphabets and spaces only." << endl;
        }

        bool capNext = true;
        for (char &c : name) {
            if (isalpha(c)) {
                c = capNext ? toupper(c) : tolower(c);
                capNext = false;
            } else {
                capNext = true;
            }
        }

        int hours;
        while (true) {
            cout << "Enter hours worked this month: ";
            if (!(cin >> hours)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid hours input! Restarting entry." << endl;
                continue;
            }

            cin.ignore(10000, '\n');

            if (hours < 0) {
                cout << "Invalid hours input! Restarting entry." << endl;
            } 
            else {
                break;
            }
        }

        int choice = 0;
        while (true) {

            cout << "Select job role:" << endl;
            cout << "1. Manager"   << endl;
            cout << "2. Developer" << endl;
            cout << "3. Tester"    << endl;
            cout << "4. Intern"    << endl;
            cout << "Enter role number: ";

            if (cin >> choice && choice >= 1 && choice <= 4) {
                cin.ignore(10000, '\n');
                cout << endl;
                break;
            }

            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Unknown role encountered. Please enter a valid role." << endl;
        }

    Role role = static_cast<Role>(choice - 1);

    double base = 0, maxBonus = 0, otRate = 0;
    switch (role) {

        case Manager:
            base = 5000; 
            maxBonus = 300; 
            otRate = 25; 
            break;

        case Developer:
            base = 4000; 
            maxBonus = 250; 
            otRate = 20; 
            break;

        case Tester:
            base = 3000; 
            maxBonus = 200; 
            otRate = 15; 
            break;

        case Intern:
            base = 1500;
            maxBonus = 150;
            otRate = 0;
            break;
    }

    double bonus = MIN_BONUS + rand() % static_cast<int>(maxBonus - MIN_BONUS + 1);
    if (hours > 160) bonus += (hours - 160) * otRate;

        double grossIncome = base + bonus;
        double tax = 0.0;

        if (grossIncome > 1000.0) {
            double portion = ((grossIncome < 3000.0) ? grossIncome : 3000.0) - 1000.0;
            tax += portion * 0.10;
        }
        if (grossIncome > 3000.0) {
            double portion = ((grossIncome < 5000.0) ? grossIncome : 5000.0) - 3000.0;
            tax += portion * 0.20;
        }
        if (grossIncome > 5000.0) {
            tax += (grossIncome - 5000.0) * 0.30;
        }

        double netSalary = grossIncome - tax;

        cout << fixed << setprecision(2);
        cout << "Employee #"     << employeeCount << ": " << name << endl;
        cout << "Base Salary: $" << base          << endl;
        cout << "Bonus: $"       << bonus         << endl;
        cout << "Tax: $"         << tax           << endl;
        cout << "Net Salary: $"  << netSalary     << endl;
        
        cout << "Add another employee? (Y/N): ";
        cin >> again;
        cin.ignore(10000, '\n');
        cout << endl;
    }

    cout << "Program ended." << endl;
    return 0;
}
