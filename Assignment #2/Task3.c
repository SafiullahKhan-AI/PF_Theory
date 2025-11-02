#include <stdio.h>

#define SIZE 4
#define power_status         (1 << 0)
#define overloadwarning     (1 << 1)
#define maintenancerequired (1 << 2)

void update_sector(int grid[][SIZE]) {
    int row, col, status, flag = 0, check;

    printf("\nEnter row number (1-%d): ", SIZE);
    scanf("%d", &row);
    printf("Enter column number (1-%d): ", SIZE);
    scanf("%d", &col);
    printf("Enter status (0=Power, 1=Overload, 2=Maintenance): ");
    scanf("%d", &status);

    while (!flag) {
        switch (status) {
        case 0:
            flag = 1;
            printf("Turn ON (1) or OFF (0): ");
            scanf("%d", &check);
            if (check == 1)
                grid[row-1][col-1] |= power_status;
            else
                grid[row-1][col-1] &= ~power_status;
            printf("Power updated at sector [%d][%d].\n", row, col);
            break;

        case 1:
            flag = 1;
            printf("Turn ON (1) or OFF (0): ");
            scanf("%d", &check);
            if (check == 1)
                grid[row-1][col-1] |= overloadwarning;
            else
                grid[row-1][col-1] &= ~overloadwarning;
            printf("Overload status updated at sector [%d][%d].\n", row, col);
            break;

        case 2:
            flag = 1;
            printf("Turn ON (1) or OFF (0): ");
            scanf("%d", &check);
            if (check == 1)
                grid[row-1][col-1] |= maintenancerequired;
            else
                grid[row-1][col-1] &= ~maintenancerequired;
            printf("Maintenance status updated at sector [%d][%d].\n", row, col);
            break;

        default:
            printf("Invalid status! Enter again (0,1,2): ");
            scanf("%d", &status);
        }
    }
}

void query_sector(int grid[][SIZE]) {
    int row, col;
    printf("\nEnter row number: ");
    scanf("%d", &row);
    printf("Enter column number: ");
    scanf("%d", &col);

    int status = grid[row-1][col-1];
    printf("\nStatus of Sector [%d][%d]:\n", row, col);

    printf("Power: %s\n", (status & power_status) ? "ON" : "OFF");
    printf("Overload: %s\n", (status & overloadwarning) ? "YES" : "NO");
    printf("Maintenance: %s\n", (status & maintenancerequired) ? "REQUIRED" : "NOT REQUIRED");
}

void run_diagnostics(int grid[][SIZE]) {
    int overloadcount = 0, maintenancecount = 0, i,j;

    for (i = 0; i < SIZE; i++) {
        for ( j = 0; j < SIZE; j++) {
            int status = grid[i][j];
            if (status & overloadwarning) overloadcount++;
            if (status & maintenancerequired) maintenancecount++;
        }
    }

    printf("\nSystem Diagnostics Report:\n");
    printf("Total overloaded sectors: %d\n", overloadcount);
    printf("Total maintenance required: %d\n", maintenancecount);
}

int main() {
    int grid[SIZE][SIZE] = {0};
    int choice, flag = 0;

    printf("\nWELCOME TO POWER GRID MONITORING SYSTEM\n");

    while (!flag) {
        printf("1. Update Sector Status\n");
        printf("2. Query Sector Status\n");
        printf("3. Run System Diagnostics\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: update_sector(grid); 
				break;
            case 2: query_sector(grid); 
				break;
            case 3: run_diagnostics(grid);
				 break;
            case 4: flag = 1; 
				break;
				
            default: printf("Invalid choice! Try again.\n");
        }
    }

    printf("\nSystem exited....\n");
    return 0;
}
