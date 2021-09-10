#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //declare variables for input, checking lengths, checking starting digits, type, counters
    long num = get_long("Number: ");
    long numc = num;
    string type = "INVALID";
    int sum = 0;
    int count = 0;
    int start = 0;
    int start2 = 0;
    int checktype = 0;
    
    
    //check length of number by dividing number by 10 each time and iterating counter
    //get first 2 digits returning num when its less than 100 and first digit by returning num when less then 10
    while (numc != 0)
    {
    
        if (numc < 10)
        {
            start = numc;
        }
        if (numc < 100 && numc > 10)
        {
            start2 = numc;
        }
        numc = numc / 10;
        count ++;
    
    
    }
    //check if digit count is too high or low
    if (count > 16 || count < 13)
    {
        printf("INVALID\n");
    }
    //check for the type of card based on starting digits and length
    //if none match, return checktype as 1, which will cause failure at final check
    else
    {
        if ((start2 == 34 && count == 15) || (start2 == 37 && count == 15))
        {
            type = "AMEX\n";
        }
        else if (start2 > 50 && start2 < 56 && count == 16)
        {
            type = "MASTERCARD\n";
        }
        else if ((count == 16 && start == 4) || (count == 13 && start == 4))
        {
            type = "VISA\n";
        }
        else
        {
            checktype = 1;
        }
    
        //add every second number * 2 and every other number * 1, to final sum as per Luhns algorithm
        int check = 0;
        while (num > 100)
        {
            sum += (num % 10);
            num = num / 10;
            check = (num % 10) * 2;
            if (check > 9)
            {
                sum += (check % 10) + (check / 10);
            }
            else
            {
                sum += check;
            }
            num = num / 10;
        }
        //leave 1 or 2 numbers at the end based on length of num being odd or even, add to sum, multiply by 2 if it's a second number required
        //if second number is double digits, return them as singles by dividing by 10 and getting remainder after dividing by 10
        if (num > 10)
        {
            sum += num % 10;
            check = (num / 10) * 2;
            if (check > 9)
            {
                sum += (check % 10) + (check / 10);
            }
            else
            {
                sum += check;
            }
        }
        else if (num > 1)
        {
            sum += num;
        }
        //check if final sum even divides into 10, also if checktype was marked due to no type match then print type else print invalid
        if (sum % 10 == 0 && checktype == 0)
        {
            printf("%s", type);
        }
        else
        {
            printf("INVALID\n");
        
        }
    }
};