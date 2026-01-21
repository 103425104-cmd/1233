#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "expenses.txt"

typedef struct {
    char date[11];
    char category[30];
    char description[50];
    float amount;
} Expense;

void addExpense();
void viewExpenses();
void calculateTotal();
void filterByCategory();

int main() {
    int choice;

    do {
        printf("\n=== Healthcare Expense Tracker ===\n");
        printf("1. Add new expense\n");
        printf("2. View all expenses\n");
        printf("3. Calculate total expenses\n");
        printf("4. Filter expenses by category\n");
        printf("5. Exit\n");

        printf("Choose an option: ");
        scanf("%d", &choice);

        getchar();

        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                viewExpenses();
                break;
            case 3:
                calculateTotal();
                break;
            case 4:
                filterByCategory();
                break;
            case 5:
                printf("Exiting application...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 5);

    return 0;
}

void addExpense() {
    FILE *file = fopen(FILE_NAME, "a");
    Expense exp;

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter date (YYYY-MM-DD): ");
    fgets(exp.date, sizeof(exp.date), stdin);
    exp.date[strcspn(exp.date, "\n")] = 0;

    printf("Enter category: ");
    fgets(exp.category, sizeof(exp.category), stdin);
    exp.category[strcspn(exp.category, "\n")] = 0;

    printf("Enter description: ");
    fgets(exp.description, sizeof(exp.description), stdin);
    exp.description[strcspn(exp.description, "\n")] = 0;

    printf("Enter amount: ");
    scanf("%f", &exp.amount);

    fprintf(file, "%s,%s,%s,%.2f\n",
            exp.date, exp.category, exp.description, exp.amount);

    fclose(file);
    printf("Expense added successfully.\n");
}

void viewExpenses() {
    FILE *file = fopen(FILE_NAME, "r");
    Expense exp;

    if (file == NULL) {
        printf("No expenses recorded yet.\n");
        return;
    }

    printf("\nDate        | Category      | Description           | Amount\n");
    printf("---------------------------------------------------------------\n");

    while (fscanf(file, "%10[^,],%29[^,],%49[^,],%f\n",
                  exp.date, exp.category, exp.description, &exp.amount) != EOF) {
        printf("%-11s | %-13s | %-20s | %.2f\n",
               exp.date, exp.category, exp.description, exp.amount);
    }

    fclose(file);
}

void calculateTotal() {
    FILE *file = fopen(FILE_NAME, "r");
    Expense exp;
    float total = 0.0;

    if (file == NULL) {
        printf("No expenses to calculate.\n");
        return;
    }

    while (fscanf(file, "%10[^,],%29[^,],%49[^,],%f\n",
                  exp.date,
                  exp.category,
                  exp.description,
                  &exp.amount) != EOF) {
        total += exp.amount;
    }

    fclose(file);
    printf("Total healthcare expenses: %.2f\n", total);
}

void filterByCategory() {
    FILE *file = fopen(FILE_NAME, "r");
    Expense exp;
    char searchCategory[30];
    int found = 0;

    if (file == NULL) {
        printf("No expenses recorded.\n");
        return;
    }

    printf("Enter category to filter: ");
    fgets(searchCategory, sizeof(searchCategory), stdin);
    searchCategory[strcspn(searchCategory, "\n")] = 0;

    printf("\nFiltered expenses:\n");

    while (fscanf(file, "%10[^,],%29[^,],%49[^,],%f\n",
                  exp.date, exp.category, exp.description, &exp.amount) != EOF) {
        if (strcmp(exp.category, searchCategory) == 0) {
            printf("%s | %s | %s | %.2f\n",
                   exp.date, exp.category, exp.description, exp.amount);
            found = 1;
        }
    }

    if (!found) {
        printf("No expenses found for this category.\n");
    }

    fclose(file);
}
