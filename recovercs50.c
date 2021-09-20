#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    //if params  arent == 2, print out usage instructions
    if (argc != 2)
    {
        printf("Usage: ./recover image");
    }

    //open 2nd parameter file to *f
    FILE *f = fopen(argv[1], "r");

    //if unable to open file, return 0
    if(!f)
    {
        return 0;
    }
    //buffer array to hold copied jpg data, counter to keep track of number of jpgs for naming
    int buffer[512];
    int counter = 0;
    //read file f into buffer
    fread(buffer, sizeof(buffer), 1, f);

    //check if first 4 header numbers match a jpg
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        //create the filename
        char *imgfile = " ";
        sprintf(imgfile, "%03i.jpg", counter);
        //add to counter
        counter++;
        //open new file to write to it
        FILE *img = fopen(imgfile, "w");
        //write what's in the buffer, to the new file
        fwrite(buffer, 512, 1, img);
        printf("%s", imgfile);
    }
}
