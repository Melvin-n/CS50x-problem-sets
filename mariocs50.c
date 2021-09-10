#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //get width from user
    int width = get_int("Width: ");
    //check for width between 1 to 8
    if (width > 0 && width < 9)
    {
        //declare counters for loops. i = how many times the loop runs, j = how many space, x, how many #'s'
        int i;
        int j;
        int x;
        int space = width;
        //one main loop with 3 loops inside. space
        for (i = 1; i < (width + 1); i++)
        {
            //1st inside loop declare amount of space at beginning of line, space decreases by 1 for next time it loops
            for (j = 1; j < space; j++)
            {
                printf(" ");
            };
            space--;
            //2nd inside loop for amount of #'s on left side. double space is added after for gap in pyramid
            for (x = 0; x < i; x++)
            {
                printf("#");
    
            };
            printf("  ");
            //3rd inside loop for amount of #'s on right side.
            for (x = 0; x < i; x++)
            {
                printf("#");
            };
            printf("\n");
        };
    }
    //if width is outside of range, call the main function again until user inputs a width number within range
    else 
    {
        main();
    }
    

};