#include "ExpenseManager.h"
#include "IncomeManager.h"
#include "FileManager.h"
#include <iostream>

void displayMenu() {
    std::cout << "\n===== Personal Finance Manager =====\n";
    std::cout << "1. Add Expense\n";
    std::cout << "2. Add Income\n";
    std::cout << "3. View Summary\n";
    std::cout << "4. Filter Expenses by Category\n";
    std::cout << "5. Generate Monthly Summary\n";
    std::cout << "6. Delete Expense\n";
    std::cout << "7. Delete Income\n";
    std::cout << "8. Save Data\n";
    std::cout << "9. Load Data\n";
    std::cout << "10. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    ExpenseManager expenseManager;
    IncomeManager incomeManager;
    FileManager fileManager;

    bool running = true;
    while (running) {
        displayMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            double amount;
            std::string category;
            std::cout << "Enter expense amount: ";
            std::cin >> amount;
            if (amount < 0) {
                std::cout << "Amount cannot be negative!\n";
                break;
            }
            std::cout << "Enter category: ";
            std::cin >> category;
            if (category.empty()) {
                std::cout << "Category cannot be empty!\n";
                break;
            }
            expenseManager.addExpense(amount, category);
            break;
        }
        case 2: {
            double amount;
            std::string source;
            std::cout << "Enter income amount: ";
            std::cin >> amount;
            if (amount < 0) {
                std::cout << "Amount cannot be negative!\n";
                break;
            }
            std::cout << "Enter source: ";
            std::cin >> source;
            if (source.empty()) {
                std::cout << "Source cannot be empty!\n";
                break;
            }
            incomeManager.addIncome(amount, source);
            break;
        }
        case 3:
            std::cout << "\nExpense Summary:\n";
            expenseManager.viewSummary();
            std::cout << "\nIncome Summary:\n";
            incomeManager.viewSummary();
            break;
        case 4: {
            std::string category;
            std::cout << "Enter category to filter: ";
            std::cin >> category;
            expenseManager.filterByCategory(category);
            break;
        }
        case 5:
            expenseManager.generateMonthlySummary();
            break;
        case 6: {
            int index;
            expenseManager.viewSummary();
            std::cout << "Enter the index of the expense to delete: ";
            std::cin >> index;
            expenseManager.deleteExpense(index);
            break;
        }
        case 7: {
            int index;
            incomeManager.viewSummary();
            std::cout << "Enter the index of the income to delete: ";
            std::cin >> index;
            incomeManager.deleteIncome(index);
            break;
        }
        case 8:
            fileManager.saveData(expenseManager, incomeManager);
            std::cout << "Data saved successfully!\n";
            break;
        case 9:
            fileManager.loadData(expenseManager, incomeManager);
            std::cout << "Data loaded successfully!\n";
            break;
        case 10:
            running = false;
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}