#include <stdio.h>

int main() {
    int cardnumber1, cardnumber2, cardnumber3, cardnumber4, cardnumber5;
    printf("Enter Card num1 (Between 1-13): ");
    scanf("%d", &cardnumber1);
    printf("Enter Card num2 (Between 1-13): ");
    scanf("%d", &cardnumber2);
    printf("Enter Card num3 (Between 1-13): ");
    scanf("%d", &cardnumber3);
    printf("Enter Card num4 (Between 1-13): ");
    scanf("%d", &cardnumber4);
    printf("Enter Card num5 (Between 1-13): ");
    scanf("%d", &cardnumber5);

    if (cardnumber1 == cardnumber2 && cardnumber2 == cardnumber3 && cardnumber4 == cardnumber5 && cardnumber1 != cardnumber4) {
        printf("Full House\n");
    } 
    else if (cardnumber1 == cardnumber2 && cardnumber2 == cardnumber4 && cardnumber3 == cardnumber5 && cardnumber1 != cardnumber3) {
        printf("Full House\n");
    } 
    else if (cardnumber1 == cardnumber2 && cardnumber2 == cardnumber5 && cardnumber3 == cardnumber4 && cardnumber1 != cardnumber3) {
        printf("Full House\n");
    } 
    else if (cardnumber1 == cardnumber3 && cardnumber3 == cardnumber4 && cardnumber2 == cardnumber5 && cardnumber1 != cardnumber2) {
        printf("Full House\n");
    } 
    else if (cardnumber1 == cardnumber3 && cardnumber3 == cardnumber5 && cardnumber2 == cardnumber4 && cardnumber1 != cardnumber2) {
        printf("Full House\n");
    }
    return 0;
}

