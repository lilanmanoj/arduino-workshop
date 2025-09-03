#include<stdio.h>

void main()
{
    int num = 2578;

    unsigned int ones = num%10;
    unsigned int tens = (num/10)%10;
    unsigned int hundreds = (num/100)%10;
    unsigned int thousands = (num/1000);

    printf("Thousands: %i\n", thousands);
    printf("Hundreds: %i\n", hundreds);
    printf("Tens: %i\n", tens);
    printf("Ones: %i\n", ones);
}