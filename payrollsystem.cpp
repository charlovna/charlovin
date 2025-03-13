#include <iostream>
#include <vector>
#include <memory>
#include <limits>

using namespace std;

// Abstract Base Class (Abstraction)
class Employee {
protected:
    int id;
    string name;
public:
    Employee(int empId, string empName) : id(empId), name(empName) {}
    virtual ~Employee() = default;

    virtual void displayPayroll() const = 0;
    int getId() const { return id; }
};

// Derived Class for Full-time Employees
class FullTimeEmployee : public Employee {
private:
    double salary;
public:
    FullTimeEmployee(int empId, string empName, double empSalary)
        : Employee(empId, empName), salary(empSalary) {}

    void displayPayroll() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Fixed Monthly Salary: $" << salary << "\n\n";
    }
};

// Derived Class for Part-time Employees
class PartTimeEmployee : public Employee {
private:
    double hourlyWage;
    int hoursWorked;
public:
    PartTimeEmployee(int empId, string empName, double wage, int hours)
        : Employee(empId, empName), hourlyWage(wage), hoursWorked(hours) {}

    void displayPayroll() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Hourly Wage: $" << hourlyWage << "\n";
        cout << "Hours Worked: " << hoursWorked << "\n";
        cout << "Total Salary: $" << hourlyWage * hoursWorked << "\n\n";
    }
};

// Derived Class for Contractual Employees
class ContractualEmployee : public Employee {
private:
    double salaryPerProject;
    int projectsCompleted;
public:
    ContractualEmployee(int empId, string empName, double salary, int projects)
        : Employee(empId, empName), salaryPerProject(salary), projectsCompleted(projects) {}

    void displayPayroll() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Contract Payment Per Project: $" << salaryPerProject << "\n";
        cout << "Projects Completed: " << projectsCompleted << "\n";
        cout << "Total Salary: $" << salaryPerProject * projectsCompleted << "\n\n";
    }
};

// Function to check if an ID already exists
bool isDuplicateId(const vector<shared_ptr<Employee>>& employees, int id) {
    for (const auto& emp : employees) {
        if (emp->getId() == id) {
            return true;
        }
    }
    return false;
}

// Function to validate numeric input
template<typename T>
T getValidInput(string prompt) {
    T value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid number.\n";
        } else {
            return value;
        }
    }
}

int main() {
    vector<shared_ptr<Employee>> employees;
    int choice;

    do {
        cout << "\nMenu\n";
        cout << "1 - Full-time Employee\n";
        cout << "2 - Part-time Employee\n";
        cout << "3 - Contractual Employee\n";
        cout << "4 - Display Payroll Report\n";
        cout << "5 - Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice! Please enter a number between 1 and 5.\n";
            continue;
        }

        if (choice >= 1 && choice <= 3) {
            int id;
            string name;

            // Get unique ID
            while (true) {
                id = getValidInput<int>("Enter Employee ID: ");
                if (isDuplicateId(employees, id)) {
                    cout << "Duplicate ID! Please enter another ID.\n";
                } else {
                    break;
                }
            }

            cout << "Enter Employee Name: ";
            cin.ignore();
            getline(cin, name);

            if (choice == 1) { // Full-time Employee
                double salary = getValidInput<double>("Enter Fixed Monthly Salary: ");
                employees.push_back(make_shared<FullTimeEmployee>(id, name, salary));
            }
            else if (choice == 2) { // Part-time Employee
                double hourlyWage = getValidInput<double>("Enter Hourly Wage: ");
                int hoursWorked = getValidInput<int>("Enter Hours Worked: ");
                employees.push_back(make_shared<PartTimeEmployee>(id, name, hourlyWage, hoursWorked));
            }
            else if (choice == 3) { // Contractual Employee
                double salaryPerProject = getValidInput<double>("Enter Salary per Project: ");
                int projectsCompleted = getValidInput<int>("Enter Number of Projects Completed: ");
                employees.push_back(make_shared<ContractualEmployee>(id, name, salaryPerProject, projectsCompleted));
            }
        }
        else if (choice == 4) { // Display Payroll Report
            cout << "\n----- Employee Payroll Report -----\n";
            if (employees.empty()) {
                cout << "No employees found!\n";
            } else {
                for (const auto& emp : employees) {
                    emp->displayPayroll();
                }
            }
        }
        else if (choice == 5) { // Exit
            cout << "Exiting program...\n";
        }
        else {
            cout << "Invalid choice! Please enter a number between 1 and 5.\n";
        }
    } while (choice != 5);

    return 0;
}
