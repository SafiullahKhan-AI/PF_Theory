#include <stdio.h>
#include <string.h>

  // PART 1
int new_book(int i, int isbns[])
{
    int temp,x;
    printf("Enter an ISBN number: ");
    scanf("%d", &temp);

    if (i >= 100)
    {
        printf("Array is full.\n");
        return i;
    }

    for ( x = 0; x < i; x++)
    {
        if (isbns[x] == temp)
        {
            printf("This ISBN '%d' is already registered.\n", temp);
            return i;
        }
    }

    isbns[i] = temp;
    return i + 1;
}

  // PART 2
void process_sale(int i, int isbns[], int quantities[])
{
    int temp, sold, x, found=0;
    printf("Enter the ISBN of Book: ");
    scanf("%d", &temp);

    printf("Enter the number of copies been sold: ");
    scanf("%d", &sold);
    
    for ( x = 0; x < i; x++)
    {
        if (isbns[x] == temp)
        {
            found = 1;
            if (quantities[x] >= sold)
            {
                quantities[x] -= sold;
                printf("Sale processed! Remaining stock: %d\n", quantities[x]);
                if (quantities[x] == 0)
                {
                    printf("Out of Stock\n");
                }
            }
            else
            {
                printf("Not enough stock... %d left Only\n", quantities[x]);
            }
            break;
        }
    }

    if (!found)
    {
        printf("ISBN not found.\n");
    }
}

      // PART 3
void report(int count, int isbns[], char titles[][20], int prices[], int quantities[])
{
    int x , found = 0;
    printf("\n--- Low Stock Report (Quantity < 5) ---\n\n");

    for ( x = 0; x < count; x++)
    {
        if (quantities[x] < 5)
        {
            found = 1;
            printf("ISBN of Book: %d\n", isbns[x]);
            printf("Title of Book: %s\n", titles[x]);
            printf("Price of Book: %d\n", prices[x]);
            printf("Quantity of Book: %d\n\n", quantities[x]);
        }
    }

    if (!found)
    {
        printf("No low stock of Book!\n");
    }
}

   // Prototypes
int new_book(int i, int isbns[]);
void process_sale(int i, int isbns[], int quantities[]);
void report(int i, int isbns[], char titles[][20], int prices[], int quantities[]);


   //MAIN FUNCTION
int main()
{
    int isbns[100];
    char titles[100][20];
    int prices[100];
    int quantities[100];
    int count = 0;
    int choice = 0;

    while (choice != 4)
    {
        printf("\n      LIBERTY BOOKS INVENTORY SYSTEM      \n");
        printf("1. Add New Book\n");
        printf("2. Process a Sale\n");
        printf("3. Generate Low Stock Report\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            count = new_book(count, isbns);

            if (count > 0 && count <= 100)
            {
                printf("Enter book title: ");
                scanf("%s", titles[count - 1]);

                printf("Enter book price: ");
                scanf("%d", &prices[count - 1]);

                printf("Enter quantity: ");
                scanf("%d", &quantities[count - 1]);

                printf("The Book is added successfully\n");
            }
            break;

        case 2:
            process_sale(count, isbns, quantities);
            break;

        case 3:
            report(count, isbns, titles, prices, quantities);
            break;

        case 4:
            printf("Thank you!\n");
            break;

        default:
            printf("Invalid choice... Try again\n");
        }
    }

    return 0;
}
