#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//declaration
float coleman(float l, float w, float s);

int main(void)
{  
    //get text input
    string text = get_string("Text: ");


    //check for type of characters in the text
    int letters = 0;
    int words = 0;
    int sentences = 0;
    int length = strlen(text);
    for (int i = 0; i < length; i ++)
    {
        //if letters, upper or lower, add to letters
        if ((text[i] >= 65 &&  text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            letters ++;
        }
        //if a space, count is as one word
        else if (text[i] == 32)
        {
            words ++;
        }
        //if a . ? ! count as a sentence
        else if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences ++;
        }


    }
    //grade = coleman function which is passed the num of l, w, and s
    int grade = coleman(letters, words, sentences);
    
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    } 
    else if (grade >= 16)
    {
        printf("Grade 16+\n");    
    }
    else
    {
        printf("Grade %i\n", (int)grade);
    }

}
//coleman function takes 3 parameters as floats, the letters, words and sentences
//gets the average letters and sentences per 100 words then plugs them into the Coleman Liau formula, returning the grade level fo the text
float coleman(float l, float w, float s)
{
    // calculate avg letters per 100 words
    float avglpw = l / (w + 1) * 100;
    //calculate avg sentences per 100 words
    float avgspw = s / (w + 1) * 100;
    //caulculate reading grade level
    float index = 0.0588 * avglpw - 0.296 * avgspw - 15.8;
    //round the index
    index = (int)round(index);
    //pass back the index (grade level) as
    return index;
}

