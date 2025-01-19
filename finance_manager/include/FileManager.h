#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "ExpenseManager.h"
#include "IncomeManager.h"
#include <nlohmann/json.hpp>
#include <fstream>

class FileManager {
public:
    void saveData(const ExpenseManager& expenseManager, const IncomeManager& incomeManager) {
        nlohmann::json jsonData;

        for (const auto& expense : expenseManager.getExpenses()) {
            jsonData["expenses"].push_back({{"amount", expense.amount}, {"category", expense.category}});
        }

        for (const auto& income : incomeManager.getIncomes()) {
            jsonData["incomes"].push_back({{"amount", income.amount}, {"source", income.source}});
        }

        std::ofstream file("data.json");
                file << jsonData.dump(4); // Write JSON data to the file with 4 spaces indentation
        file.close();
    }

    void loadData(ExpenseManager& expenseManager, IncomeManager& incomeManager) {
        std::ifstream file("data.json");
        if (!file.is_open()) {
            std::cout << "Failed to open data.json for loading.\n";
            return;
        }

        nlohmann::json jsonData;
        file >> jsonData;

        // Load expenses
        if (jsonData.contains("expenses")) {
            for (const auto& expense : jsonData["expenses"]) {
                expenseManager.addExpense(expense["amount"], expense["category"]);
            }
        }

        // Load incomes
        if (jsonData.contains("incomes")) {
            for (const auto& income : jsonData["incomes"]) {
                incomeManager.addIncome(income["amount"], income["source"]);
            }
        }

        file.close();
    }
};

#endif // FILE_MANAGER_H