#include <stdio.h>
double calc_repay(double loan, double interestRate, int yrs, double installment)
{
    if(loan <= 0 || yrs == 0){
        return 0;}

    double AfterInterest = loan * (1 + interestRate / 100.0);
    double remaining = AfterInterest - installment;
    if(remaining > 0){
        printf("Year %d: Remaining loan = %.2f\n", yrs, remaining);
    }
    else{
        printf("Year %d: Remaining loan = %.2f\n", yrs, 0.0);
    }
    return installment + calc_repay(remaining, interestRate, yrs - 1, installment);
}

int main(){
    double loan = 300000;
    double interestRate = 5;
    int yrs = 5;
    double installment = 40000;
    double totalPaid = calc_repay(loan, interestRate, yrs, installment);
    printf("Total repayment over %d years = %.2f\n", yrs, totalPaid);
}
