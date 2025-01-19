#ifndef EXPENSE_MANAGER_H
#define EXPENSE_MANAGER_H

#include <vector>
#include <string>
#include <iostream>
#include <map>

struct Expense {
    double amount;
    std::string category;
};

class ExpenseManager {
private:
    std::vector<Expense> expenses;

public:
    void addExpense(double amount, const std::string& category) {
        expenses.push_back({amount, category});
    }

    void viewSummary() const {
        for (size_t i = 0; i < expenses.size(); ++i) {
            const auto& expense = expenses[i];
            std::cout << i << ". Category: " << expense.category << ", Amount: " << expense.amount << "\n";
        }
    }

    void filterByCategory(const std::string& category) const {
        bool found = false;
        for (const auto& expense : expenses) {
            if (expense.category == category) {
                std::cout << "Category: " << expense.category << ", Amount: " << expense.amount << "\n";
                found = true;
            }
        }
        if (!found) {
            std::cout << "No expenses found for category: " << category << "\n";
        }
    }

    void generateMonthlySummary() const {
        double totalExpenses = 0.0;
        std::map<std::string, double> categoryTotals;

        for (const auto& expense : expenses) {
            totalExpenses += expense.amount;
            categoryTotals[expense.category] += expense.amount;
        }

        std::cout << "\nMonthly Expense Summary:\n";
        std::cout << "Total Expenses: " << totalExpenses << "\n";
        for (const auto& [category, total] : categoryTotals) {
            std::cout << "Category: " << category << ", Total: " << total << "\n";
        }
    }

    void deleteExpense(size_t index) {
        if (index < expenses.size()) {
            expenses.erase(expenses.begin() + index);
            std::cout << "Expense deleted successfully!\n";
        } else {
            std::cout << "Invalid index!\n";
        }
    }

    const std::vector<Expense>& getExpenses() const {
        return expenses;
    }
};

#endif // EXPENSE_MANAGER_H