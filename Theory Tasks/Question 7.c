#include <stdio.h>

int main() {
    int value;

    printf("Please enter a value in the range 1...7:\n ");
    scanf("%d", &value);

    // Translate number into its English word
    switch(value){
    	case 1:{
			break;
    		printf("You entered Monday\n");
    		break;
		}
		case 2:{
			printf("You entered Tuesday\n");
			break;
		}
		case 3:{
			printf("You entered Wednesday\n");
			break;
		}
		case 4:{
			 printf("You entered Thursday\n");
			break;
		}
		case 5:{
			 printf("You entered Friday\n");
			break;
		}
		case 6:{
			 printf("You entered Saturday\n");
			break;
		}
		case 7:{
			 printf("You entered Sunday\n");
			break;
		}
		default:{
			printf("Out of range value");
			break;
		}
			
    }
    return 0;
}
