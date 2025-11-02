#include <stdio.h>
#include <string.h>

void reverse_string(char str[])
{
    int i , len = strlen(str);
    for ( i = 0; i < len / 2; i++)
    {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

char toggle_bits(char ch)
{
    ch = ch ^ (1 << 1);
    ch = ch ^ (1 << 4);
    return ch;
}

void encode_message(char message[])
{
    reverse_string(message);
    int i;
    for (i = 0; message[i] != '\0'; i++)
    {
        message[i] = toggle_bits(message[i]);
    }
    printf("Encoded Message: %s\n", message);
}


void decode_message(char message[])
{
	int i;
    for ( i = 0; message[i] != '\0'; i++)
    {
        message[i] = toggle_bits(message[i]);
    }
    reverse_string(message);
    printf("Decoded Message: %s\n", message);
}

int main()
{
    char message[200];
    int choice;
    int flag = 0;

    while (!flag)
    {
        printf("\n--------------- MENU ---------------\n");
        printf("1: ENCODE Message\n");
        printf("2: DECODE Message\n");
        printf("3: EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            printf("Enter the message to encode: ");
            fgets(message, sizeof(message), stdin);
            message[strcspn(message, "\n")] = '\0';
            encode_message(message);
            break;

        case 2:
            printf("Enter the message to decode: ");
            fgets(message, sizeof(message), stdin);
            message[strcspn(message, "\n")] = '\0';
            decode_message(message);
            break;

        case 3:
            printf("Exiting Program!!!\n");
            flag = 1;
            break;

        default:
            printf("Invalid Option...try again\n");
            break;
        }
    }

    return 0;
}
