#include "IncomeManager.h"

void IncomeManager::addIncome(double amount, const std::string& source) {
    incomes.push_back({amount, source});
}

void IncomeManager::viewSummary() const {
    for (size_t i = 0; i < incomes.size(); ++i) {
        const auto& income = incomes[i];
        std::cout << i << ". Source: " << income.source << ", Amount: " << income.amount << "\n";
    }
}

void IncomeManager::deleteIncome(size_t index) {
    if (index < incomes.size()) {
        incomes.erase(incomes.begin() + index);
        std::cout << "Income deleted successfully!\n";
    } else {
        std::cout << "Invalid index!\n";
    }
}
