#include <stdio.h>
int main(){
	int num;
	int zeros, ones,twos,threes,fours,fives,sixs,sevens,eights,nines;
	zeros= 0;
	ones = 0;
	threes= 0;
	fours= 0;
	fives= 0;
	sixs= 0;
	sevens= 0;
	eights= 0;
	nines= 0;
	printf("Enter Number between 0-9: ");
	scanf("%d",&num);
	while(num>=0 && num<=9){
		if(num==0){
			zeros= zeros +1;
		}
		else if(num==1){
			ones= ones +1;
		}
		else if(num==2){
			twos= twos +1;
		}
		else if(num==3){
			threes= threes +1;
		}
		else if(num==4){
			fours= fours +1;
		}
		else if(num==5){
			fives= fives +1;
		}
		else if(num==6){
			sixs= sixs +1;
		}
		else if(num==7){
			sevens= sevens +1;
		}
		else if(num==8){
			eights= eights +1;
		}
		else if(num==9){
			nines= nines +1;
		
		}
		printf("Enter Number between 0-9: ");
		scanf("%d",&num);
	}
	printf("Number      |   Number of occurence\n");
	printf("-----------------------------------\n");
	printf("  0         |          %d           \n",zeros);
	printf("-----------------------------------\n");
	printf("  1         |          %d             \n",ones);
	printf("-----------------------------------\n");
	printf("  2         |          %d            \n",twos);
	printf("-----------------------------------\n");
	printf("  3         |          %d            \n",threes);
	printf("-----------------------------------\n");
	printf("  4         |          %d           \n", fours);
	printf("-----------------------------------\n");
	printf("  5         |          %d          \n", fives);
	printf("-----------------------------------\n");
	printf("  6         |          %d          \n", sixs);
	printf("-----------------------------------\n");
	printf("  7         |          %d          \n", sevens);
	printf("-----------------------------------\n");
	printf("  8         |          %d          \n", eights);
	printf("-----------------------------------\n");
	printf("  9         |          %d         \n", nines);
}
