#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //if params  arent == 2, print out usage instructions
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }
    //OPEN MEM CARD
    //open 2nd parameter file to *f
    FILE *f = fopen(argv[1], "r");

    //if unable to open file, return 0
    if(!f)
    {
        return 1;
    }

    BYTE buffer[512];  //read file f into buffer of 512
    int counter = 0;
    int firstjpeg = 0;
    char imgfile[8];
    FILE *currentfile;
    int foundjpg = 0;
    //REPEAT UNTIL END OF CARD
    while(fread(buffer, sizeof(BYTE), 512, f) != 0) //while theres still 512 bytes remaining in card
    {
        //READ 512 BYTES INTO BUFFER
        //fread(buffer, sizeof(BYTE), 512, f);

        //IF START OF NEW JPG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            foundjpg = 1;
            //IF FIRST JPG
            if (firstjpeg == 0)
            {
                firstjpeg = 1;
            }
            //IF NOT FIRST THEN CLOSE FILE, OPEN NEW FILE
            else
            {
                fclose(currentfile);
            }
            sprintf(imgfile, "%03i.jpg", counter); //create filename
            currentfile = fopen(imgfile, "w"); //assign new file
            counter++;
            fwrite(buffer, sizeof(BYTE), 512, currentfile);
        }
        //ELSE IF ALREADY FOUND JPG
        else
        {
            if(foundjpg == 1)
            {
                fwrite(buffer, sizeof(BYTE), 512, currentfile); //write what's in the buffer, to the new file
            }

        }
    //CLOSE ANY REMANING FILES

    }
    fclose(currentfile);
    fclose(f);
    return 0;
}
