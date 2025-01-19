#include "DataVisualizer.h"
#include <iostream>
#include <map>

void DataVisualizer::visualizeExpensesByCategory(const ExpenseManager& expenseManager) {
    std::map<std::string, double> categoryTotals;

    for (const auto& expense : expenseManager.getExpenses()) {
        categoryTotals[expense.category] += expense.amount;
    }

    std::cout << "\nExpense Breakdown by Category:\n";
    for (const auto& [category, total] : categoryTotals) {
        std::cout << "Category: " << category << ", Total: " << total << "\n";
    }
}

void DataVisualizer::visualizeMonthlyTrends(const ExpenseManager& expenseManager, const IncomeManager& incomeManager) {
    double totalExpenses = 0.0, totalIncome = 0.0;

    for (const auto& expense : expenseManager.getExpenses()) {
        totalExpenses += expense.amount;
    }

    for (const auto& income : incomeManager.getIncomes()) {
        totalIncome += income.amount;
    }

    double netSavings = totalIncome - totalExpenses;

    std::cout << "\nMonthly Financial Summary:\n";
    std::cout << "Total Income: " << totalIncome << "\n";
    std::cout << "Total Expenses: " << totalExpenses << "\n";
    std::cout << "Net Savings: " << netSavings << "\n";
}