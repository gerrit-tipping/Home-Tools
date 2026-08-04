#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(void) {

    //Definitions Section
    char RawIn[100];

    double numbers[100];
    char operators[100];

    int numCount = 0;
    int opCount = 0;


    //Input Section
    printf("Input Data Below\n");
    fgets(RawIn, sizeof(RawIn), stdin);


    //Data Processing Section

    char *p = RawIn;

    while (*p != '\0') {
        if (isdigit(*p) || *p == '.') {
            char *end;
            numbers[numCount++] = strtod(p, &end);
            p = end;
        }
        else {
            operators[opCount++] = *p;
            p++;
        }
    }


   //Debug
   for (int i = 0; i < numCount; i++)
       printf("numbers[%d] = %f\n", i, numbers[i]);

    for (int i = 0; i < opCount; i++)
        printf("operators[%d] = %c\n", i, operators[i]);



    //Output Section
    printf("You Inputed: %s\n", RawIn);


    //Ending Section
    sleep(10);

    return 0;
}
