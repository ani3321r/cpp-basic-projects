#ifndef DATA_VISUALIZER_H
#define DATA_VISUALIZER_H

#include "ExpenseManager.h"
#include "IncomeManager.h"

class DataVisualizer {
public:
    /**
     * Visualize expense breakdown by category.
     * @param expenseManager - The manager holding expense data.
     */
    static void visualizeExpensesByCategory(const ExpenseManager& expenseManager);

    /**
     * Visualize monthly trends of income, expenses, and net savings.
     * @param expenseManager - The manager holding expense data.
     * @param incomeManager - The manager holding income data.
     */
    static void visualizeMonthlyTrends(const ExpenseManager& expenseManager, const IncomeManager& incomeManager);
};

#endif // DATA_VISUALIZER_H