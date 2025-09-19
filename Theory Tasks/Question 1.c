#include <stdio.h>
#include <string.h>

int main() {
    system("cls");

    int MaxLimit = 10000;
    int Amount;
    char country[30] = "Pakistan";
    char country2[30] = "UAE";
    char selectedCountry[30];
    int hour, num_Of_Transactions = 0;
    int Flag = 0;
    int choice;

    printf("Select your country:\n");
    printf("1. Pakistan\n");
    printf("2. UAE\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Country selected PAKISTAN\n");
            strcpy(selectedCountry, country);
            break;
        case 2:
            printf("Country selected UAE\n");
            strcpy(selectedCountry, country2);
            break;

        default:
            printf("Invalid choice\n");
            return 0;
    }
    printf("Enter current hour (0-23): ");
    scanf("%d", &hour);
    if (hour > 20) {
        printf("Transactions are not allowed after 8 pm.\n");
        return 0;
    }
    printf("Enter the total amount: ");
    scanf("%d", &Amount);
    while (Amount < MaxLimit && Flag == 0) {
        MaxLimit = MaxLimit - Amount;
        num_Of_Transactions = num_Of_Transactions + 1;
        printf("Your transaction is successful\n");
        printf("You still have %d limit left\n", MaxLimit);

        if (num_Of_Transactions >= 3) {
            printf("You have reached the maximum number of transactions allowed (3)\n");
            break;
        }
        printf("If you want to exit just type 1 (otherwise type 0): ");
        scanf("%d", &Flag);
        if (Flag == 0) {
            printf("Enter next amount: ");
            scanf("%d", &Amount);
        }
    }
    if (Amount >= MaxLimit) {
        if (Amount == MaxLimit) {
            printf("Your transaction is successful but you don't have any limit left\n");
        } else {
            printf("You have reached your daily limit!!!\n");
        }
    } else if (Flag == 1) {
        printf("THANK YOU FOR USING\n");
    }
    return 0;
}

