#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    //check if argc has 2 more arguemnts, if more or less, output error
   
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //check for length of str to be 26, if not, otutput error
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        for (int i = 0; i < strlen(argv[1]); i ++)
        {   
            //check for contents of key, if they are all valid letter characters
            if (argv[1][i] < 65 || argv[1][i] > 122 || (argv[1][i] > 90 && argv[1][i] < 97))
            {
                printf("Invalid characters used, please only use letters");
                return 1;
            }
            //check if there are any duplicate keys
            else if (argv[1][i] == argv[1][i + 1])
            {
                printf("Key contains duplicates");
                return 1;
            }
        }
    
        //if 2 arguments have been passed and string is more 26 chars, continue with program
        //get string of text  from user
        string plaintext = get_string("plaintext: ");
        //print out ciphertext before looping through the string
        printf("ciphertext: ");
        //loop through each letter of the string, check ifor caps/lower and maintain after decryption.
        //print each corresponding letter of the key out 
        for (int i = 0; i < strlen(plaintext); i ++)
        {   
            if (plaintext[i] > 96 && plaintext[i] < 123)
            {
                printf("%c", tolower(argv[1][plaintext[i] - 97]));
            } 
            else if (plaintext[i] > 64 && plaintext[i] < 91)
            {
                printf("%c", toupper(argv[1][plaintext[i] - 65]));
            }
            else
            {
                printf("%c", plaintext[i]);
            }
            
        }
        printf("\n");
    }
}