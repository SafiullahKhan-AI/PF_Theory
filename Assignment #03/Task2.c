#include <stdio.h>

void calc_fuel(int fuel_amount, int consumption, int recharge, int s_bonus, int planet, int total_planets){
    if(fuel_amount <= 0){
        printf("Mission Failed... Fuel depleted before planet %d.\n", planet);
        return;
    }
    if(planet > total_planets){
        printf("Mission Successful... Spacecraft journey completed.\n");
        return;
    }

    fuel_amount -= consumption;
    fuel_amount += recharge;

    if(planet % 4 == 0){
        fuel_amount += s_bonus;
    }

    if(fuel_amount > 0){
        printf("Planet %d: Fuel Remaining = %d\n", planet, fuel_amount);}
    else{
        printf("Planet %d: Fuel Remaining = 0\n", planet);}

    calc_fuel(fuel_amount, consumption, recharge, s_bonus, planet + 1, total_planets);
}

int main(){
    int fuel_amount = 500;
    int consumption = 70;
    int recharge = 20;
    int s_bonus = 100;
    int total_planets = 10;
    calc_fuel(fuel_amount, consumption, recharge, s_bonus, 1, total_planets);
}
