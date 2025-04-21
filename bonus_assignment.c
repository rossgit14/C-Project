//Ross Carnevale - 220656385

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[100];
    int id;
    float salary;
    char department[50];
    int yearsOfExperience;
    float performanceScore;
} Employee;

Employee *employees = NULL; // Dynamically growing array of employees
int employeeCount = 0;

// Function prototypes
void addEmployee();
void updateEmployee();
void displayEmployees();
void searchEmployeeByName();
void sortEmployeesByPerformance();
void freeMemory();

int main() {
    int choice;
    do {
        printf("\nEmployee Performance Management System\n");
        printf("1. Add Employee\n");
        printf("2. Update Employee\n");
        printf("3. Display All Employees\n");
        printf("4. Search Employee by Name\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear input buffer

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                updateEmployee();
                break;
            case 3:
                displayEmployees();
                break;
            case 4:
                searchEmployeeByName();
                break;
            case 5:
                printf("Exiting...\n");
                freeMemory();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void addEmployee() {
    employees = realloc(employees, (employeeCount + 1) * sizeof(Employee));
    if (employees == NULL) {
        printf("\nMemory allocation failed!\n");
        return;
    }

    Employee *newEmployee = &employees[employeeCount];
    printf("Enter name of employee: ");
    fgets(newEmployee->name, sizeof(newEmployee->name), stdin);
    newEmployee->name[strcspn(newEmployee->name, "\n")] = '\0'; // Remove newline

    printf("Enter employee ID: ");
    scanf("%d", &newEmployee->id);

    printf("Enter salary: ");
    scanf("%f", &newEmployee->salary);

    getchar(); // Clear input buffer
    printf("Enter department: ");
    fgets(newEmployee->department, sizeof(newEmployee->department), stdin);
    newEmployee->department[strcspn(newEmployee->department, "\n")] = '\0'; // Remove newline

    printf("Enter years of experience: ");
    scanf("%d", &newEmployee->yearsOfExperience);

    newEmployee->performanceScore = (0.3 * newEmployee->yearsOfExperience) + (0.7 * newEmployee->salary / 1000);
    employeeCount++;
    printf("\nEmployee added successfully!\n");
}

void updateEmployee() {
    int id, i;
    printf("Enter Employee ID to update: ");
    scanf("%d", &id);

    for (i = 0; i < employeeCount; i++) {
        if (employees[i].id == id) {
            printf("Enter new salary: ");
            scanf("%f", &employees[i].salary);

            getchar(); // Clear input buffer
            printf("Enter new department: ");
            fgets(employees[i].department, sizeof(employees[i].department), stdin);
            employees[i].department[strcspn(employees[i].department, "\n")] = '\0'; // Remove newline

            employees[i].performanceScore = (0.3 * employees[i].yearsOfExperience) + (0.7 * employees[i].salary / 1000);
            printf("\nEmployee information updated successfully!\n");
            return;
        }
    }
    printf("\nEmployee ID not found.\n");
}

void displayEmployees() {
    sortEmployeesByPerformance();

    printf("\nEmployee Records (sorted by Performance Score):\n");
    for (int i = 0; i < employeeCount; i++) {
        printf("\nName: %s\n", employees[i].name);
        printf("Employee ID: %d\n", employees[i].id);
        printf("Salary: %.2f\n", employees[i].salary);
        printf("Department: %s\n", employees[i].department);
        printf("Years of Experience: %d\n", employees[i].yearsOfExperience);
        printf("Performance Score: %.2f\n", employees[i].performanceScore);
    }
}

void searchEmployeeByName() {
    char name[100];
    printf("Enter name to search: ");
    getchar(); // Clear input buffer
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline

    int found = 0;
    for (int i = 0; i < employeeCount; i++) {
        if (strstr(employees[i].name, name) != NULL) {
            if (!found) {
                printf("\nSearch Results:\n");
                found = 1;
            }
            printf("\nName: %s\n", employees[i].name);
            printf("Employee ID: %d\n", employees[i].id);
            printf("Salary: %.2f\n", employees[i].salary);
            printf("Department: %s\n", employees[i].department);
            printf("Years of Experience: %d\n", employees[i].yearsOfExperience);
            printf("Performance Score: %.2f\n", employees[i].performanceScore);
        }
    }
    if (!found) {
        printf("\nNo matching records found.\n");
    }
}

void sortEmployeesByPerformance() {
    for (int i = 0; i < employeeCount - 1; i++) {
        for (int j = 0; j < employeeCount - i - 1; j++) {
            if (employees[j].performanceScore < employees[j + 1].performanceScore) {
                Employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
}

void freeMemory() {
    free(employees);
}

