#include <stdio.h>

int push(int stack[], int top, int maxsize) {
    int element;
    if (top == maxsize) {
        printf("Error!! Stack overflow (stack is full)\n");
        return top;
    }
    printf("Enter the element you want to push: ");
    scanf("%d", &element);
    stack[top] = element;
    top++;
    printf("Item pushed !\n");
    return top;
}

int pop(int stack[], int top) {
    if (top == 0) {
        printf("Error!! Stack underflow (stack is empty)\n");
        return top;
    }
    top--;
    printf("Your top item %d is successfully removed.\n", stack[top]);
    return top;
}

void peek(int stack[], int top) {
    if (top == 0) {
        printf("===Stack is empty===\n");
    } else {
        printf("Top element: %d\n", stack[top - 1]);
    }
}

void display(int stack[], int top) {
    if (top == 0) {
        printf("===Stack is empty===\n");
    } else {
        printf("Stack elements (bottom -> top): ");
        int i;
        for (i = 0; i < top; i++) {
            printf("%d --- ", stack[i]);
        }
        printf("\n");
    }
}

int main() {
    int stack[10];
    int top = 0;
    int choice;
    int maxsize = 10;
    int exitFlag = 0;

    while (!exitFlag) {
        printf("\n--------------- MENU ---------------\n");
        printf("1. PUSH (Insert an element)\n");
        printf("2. POP (Remove top element)\n");
        printf("3. PEEK (View top element)\n");
        printf("4. DISPLAY (Show all elements)\n");
        printf("5. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                top = push(stack, top, maxsize);
                break;
            case 2:
                top = pop(stack, top);
                break;
            case 3:
                peek(stack, top);
                break;
            case 4:
                display(stack, top);
                break;
            case 5:
                printf("Exiting the program\n");
                exitFlag = 1;
                break;
            default:
                printf("Invalid Option , Try again\n");
        }
    }

    return 0;
}

