#include "FileManager.h"
#include <iostream>
#include <fstream>

void FileManager::saveData(const ExpenseManager& expenseManager, const IncomeManager& incomeManager) {
    nlohmann::json jsonData;

    for (const auto& expense : expenseManager.getExpenses()) {
        jsonData["expenses"].push_back({{"amount", expense.amount}, {"category", expense.category}});
    }

    for (const auto& income : incomeManager.getIncomes()) {
        jsonData["incomes"].push_back({{"amount", income.amount}, {"source", income.source}});
    }

    std::ofstream file("data.json");
    if (file.is_open()) {
        file << jsonData.dump(4);
        file.close();
        std::cout << "Data saved successfully!\n";
    } else {
        std::cout << "Failed to open data.json for saving.\n";
    }
}

void FileManager::loadData(ExpenseManager& expenseManager, IncomeManager& incomeManager) {
    std::ifstream file("data.json");
    if (!file.is_open()) {
        std::cout << "Failed to open data.json for loading.\n";
        return;
    }

    nlohmann::json jsonData;
    file >> jsonData;

    if (jsonData.contains("expenses")) {
        for (const auto& expense : jsonData["expenses"]) {
            expenseManager.addExpense(expense["amount"], expense["category"]);
        }
    }

    if (jsonData.contains("incomes")) {
        for (const auto& income : jsonData["incomes"]) {
            incomeManager.addIncome(income["amount"], income["source"]);
        }
    }

    file.close();
    std::cout << "Data loaded successfully!\n";
}