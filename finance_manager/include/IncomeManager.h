#ifndef INCOME_MANAGER_H
#define INCOME_MANAGER_H

#include <vector>
#include <string>
#include <iostream>

struct Income {
    double amount;
    std::string source;
};

class IncomeManager {
private:
    std::vector<Income> incomes;

public:
    void addIncome(double amount, const std::string& source) {
        incomes.push_back({amount, source});
    }

    void viewSummary() const {
        for (size_t i = 0; i < incomes.size(); ++i) {
            const auto& income = incomes[i];
            std::cout << i << ". Source: " << income.source << ", Amount: " << income.amount << "\n";
        }
    }

    void deleteIncome(size_t index) {
        if (index < incomes.size()) {
            incomes.erase(incomes.begin() + index);
            std::cout << "Income deleted successfully!\n";
        } else {
            std::cout << "Invalid index!\n";
        }
    }

    const std::vector<Income>& getIncomes() const {
        return incomes;
    }
};

#endif // INCOME_MANAGER_H