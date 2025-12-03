#include <stdio.h>
#include <string.h>

struct Employee{
    int id;
    char name[50];
    char designation[50];
    float salary;
};

void displayEmployees(struct Employee emp[], int n){
    printf("ID\t\tName\t\tDesignation\t\tSalary\n");

    for(int i = 0; i < n; i++){
        printf("%d\t\t%-15s\t\t%-20s%.2f\n",
               emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
    }
}

void find_highest_salary(struct Employee emp[], int n){
    int x = 0;  

    for(int i = 1; i < n; i++){
        if(emp[i].salary > emp[x].salary) {
            x = i;
        }
    }

    printf("\nEmployee with Highest Salary:\n");
    printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
           emp[x].id, emp[x].name, emp[x].designation, emp[x].salary);
}


void searchEmployee(struct Employee emp[], int n) {
    int choice;
    printf("\nSearch by:\n1. Employee ID\n2. Name\nEnter choice: ");
    scanf("%d", &choice);

    if(choice == 1) {
        int id;
        printf("Enter Employee ID: ");
        scanf("%d", &id);

        for(int i = 0; i < n; i++) {
            if (emp[i].id == id) {
                printf("\nRecord Found:\n");
                printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
                       emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
            }
        }
        printf("Employee with ID %d not found.\n", id);
    }

    else if(choice == 2){
        char name[50];
        printf("Enter Name: ");
        scanf("%s", name);

        for(int i = 0; i < n; i++){
            if (strcmp(emp[i].name, name) == 0) {
                printf("\nRecord Found:\n");
                printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
                       emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
                return;
            }
        }
        printf("Employee with Name '%s' not found.\n", name);
    }

    else{
        printf("Invalid choice.\n");
    }
}

int main(){
    int n;
    printf("Enter number of employees: ");
    scanf("%d", &n);
    
    struct Employee emp[n];
    for(int i = 0; i < n; i++){
        printf("\nEnter details for Employee %d\n", i + 1);
        printf("ID: ");
        scanf("%d", &emp[i].id);
        printf("Name: ");
        scanf("%s", emp[i].name);
        printf("Designation: ");
        scanf("%s", emp[i].designation);
        printf("Salary: ");
        scanf("%f", &emp[i].salary);
    }
    displayEmployees(emp, n);
    find_highest_salary(emp, n);
    searchEmployee(emp, n);
}

// for 10% Bonus on Salary
void Bonus(struct Employee emp[], int n, float threshold) {
    for (int i = 0; i < n; i++) {
        if (emp[i].salary < threshold) {
            emp[i].salary = emp[i].salary + (emp[i].salary * 0.10);
        }
    }
}
