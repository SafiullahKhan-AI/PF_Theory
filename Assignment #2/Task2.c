#include <stdio.h>
#include <string.h>

		// CUSTOMER INFO
void customer_information(char name[], long long *cnic) {
    int i = 0; char ch;
    printf("Enter your full name: ");
    getchar();
    while ((ch = getchar()) != '\n' && i < 199) name[i++] = ch;
    name[i] = '\0';

    printf("Enter your CNIC number (13 digits): ");
    scanf("%lld", cnic);
    while (*cnic < 1000000000000 || *cnic > 9999999999999) {
        printf("Enter a valid 13-digit CNIC number: ");
        scanf("%lld", cnic);
    }
}

		// DISPLAY 
void display_inventory(int product_code[], int quantity[], int price_product[], int size) {
    int j; 
    printf("\nProduct Code      Quantity in Stock        Price \n");
    printf("--------------------------------------------------------\n");
    for (j = 0; j < size; j++)
        printf("%5.3d %20d %21d\n", product_code[j], quantity[j], price_product[j]);
    printf("--------------------------------------------------------\n");
}

		// ADD TO CART
int add_to_cart(int product_code[], int quantity[], int price[], int cart_code[], int cart_quantity[], int cart_index, int size) {
    int code, qty, i;
    printf("Enter product code: ");
    scanf("%d", &code);

    for (i = 0; i < size; i++) {
        if (product_code[i] == code) {
            printf("Enter quantity: ");
            scanf("%d", &qty);
            if (qty <= quantity[i] && qty > 0) {
                cart_code[cart_index] = code;
                cart_quantity[cart_index] = qty;
                cart_index++;
                quantity[i] -= qty;
                printf("Item added to cart and inventory updated!\n");
                return cart_index;
            } else {
                printf("Not enough stock---- Only %d left.\n", quantity[i]);
                return cart_index;
            }
        }
    }
    printf("Product not found---\n");
    return cart_index;
}

		// UPDATE INVENTORY 
	void update_inventory(int product_code[], int quantity[], int cart_code[], int cart_quantity[], int cart_index, int size)
	{
    if (cart_index == 0) {
        printf("No items in cart to update!\n");
        return;
    }
    int code, i, j, add_qty;
    printf("Enter product code from your cart to update quantity: ");
    scanf("%d", &code);
    
    for (i = 0; i < cart_index; i++) {
        if (code == cart_code[i]) {
            
            for (j = 0; j < size; j++) {
                if (product_code[j] == code) {
                    printf("Current cart quantity for this product: %d\n", cart_quantity[i]);
                    printf("Enter additional quantity to purchase: ");
                    scanf("%d", &add_qty);
                    if (add_qty > 0 && add_qty <= quantity[j]) {
                        cart_quantity[i] += add_qty;
                        quantity[j] -= add_qty;
                        printf("Inventory and cart updated: now %d of product %03d in cart. Inventory left: %d\n", cart_quantity[i], code, quantity[j]);
                    } else {
                        printf("Not enough stock or invalid quantity! Only %d left in inventory.\n", quantity[j]);
                    }
                    return;
                }
            }
        }
    }
    printf("Product not found!!!\n");
	}
	//Total
	int calculate_total_bill(int cart_code[], int cart_quantity[], int product_code[], int price_product[], int size, int cart_index)
	{
    int i, j, total = 0;
    for (i = 0; i < cart_index; i++)
        for (j = 0; j < size; j++)
            if (cart_code[i] == product_code[j])
                total += cart_quantity[i] * price_product[j];
    return total;
	}
	// Display Bill
	void display_bill(int cart_code[], int cart_quantity[], int product_code[], int price_product[], int size, int cart_index)
	{
    if (cart_index == 0) { printf("Your cart is empty!!!\n"); return; }
    int total = calculate_total_bill(cart_code, cart_quantity, product_code, price_product, size, cart_index);
    printf("Total Bill: Rs %d\n", total);
	}
	// Invoice Generate
	void show_invoice(char name[], long long cnic, int cart_code[], int cart_quantity[], int product_code[], int price_product[], int size, int cart_index)
	{
    if (cart_index == 0) { printf("No items in cart! Please Add Items in Cart...\n"); return; }
    int total = calculate_total_bill(cart_code, cart_quantity, product_code, price_product, size, cart_index);
    char promo[20];

    printf("\n====== INVOICE ======\n");
    printf("Customer: %s\n", name);
    printf("CNIC: %lld\n", cnic);
    printf("\nItems Purchased:\n");
    int i, j;
    for (i = 0; i < cart_index; i++)
        for (j = 0; j < size; j++)
            if (cart_code[i] == product_code[j])
                printf("Code: %03d | Quantity: %d | Price: %d | Subtotal: Rs %d\n", cart_code[i], cart_quantity[i], price_product[j], cart_quantity[i] * price_product[j]);
    printf("\nTotal Bill: Rs %d\n", total);
    printf("Enter promocode (if any): ");
    scanf("%s", promo);

    if (strcmp(promo, "Eid2025") == 0) {
        int discounted = (int)(total * 0.75);
        printf("Promocode applied! 25%% discount.\n");
        printf("Bill without discount: Rs %d\n", total);
        printf("Final Bill (with discount): Rs %d\n", discounted);
    } else {
        printf("No discount applied.\n");
        printf("Final Bill: Rs %d\n", total);
    }
    printf("=============================\n");
}

int main()
{
    char name[200];
    long long cnic;
    int choice;
    int product_code[4] = {1, 2, 3, 4}; 
    int quantity[4] = {50, 10, 20, 8};
    int price_product[4] = {100, 200, 300, 150};
    int cart_code[10];
    int cart_quantity[10];
    int cart_index = 0;

    printf("Welcome to SuperMarket Management System\n\n");
    customer_information(name, &cnic);

    while (1) {
        printf("\n==== SUPERMARKET MENU ====\n");
        printf("1. Display Inventory\n");
        printf("2. Add Item to Cart\n");
        printf("3. Update Inventory (add more to cart item)\n");
        printf("4. Display Total Bill\n");
        printf("5. Show Invoice\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
            display_inventory(product_code, quantity, price_product, 4);
        else if (choice == 2)
            cart_index = add_to_cart(product_code, quantity, price_product, cart_code, cart_quantity, cart_index, 4);
        else if (choice == 3)
            update_inventory(product_code, quantity, cart_code, cart_quantity, cart_index, 4);
        else if (choice == 4)
            display_bill(cart_code, cart_quantity, product_code, price_product, 4, cart_index);
        else if (choice == 5)
            show_invoice(name, cnic, cart_code, cart_quantity, product_code, price_product, 4, cart_index);
        else if (choice == 6) {
            printf("Exiting system...Thanks For Shopping\n");
            break;
        }
        else
            printf("Invalid Option!\n");
    }

    return 0;
}



