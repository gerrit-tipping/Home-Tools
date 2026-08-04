#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

//operator definitions
double add(double a, double b) { return a + b; }
double sub(double a, double b) { return a - b; }


int main(void) {

    //Definitions Section
    char RawIn[100];

    double numbers[100];
    double output[100];
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


    //Calculation
    for (int i = 0; i < opCount-1; i++)
    {
        double a = numbers[i];
        double b = numbers[i+1];





        double (*operation)(double, double) =NULL;
        switch (operators[i]) {
            case '+': operation = add; break;
            case '-': operation = sub; break;
            default:
                printf("Invalid operator: %c\n", operators[i]);
                return 1;
        }

        if (operation != NULL)
            {
            numbers[i+1]= operation(a, b);
            }


    }







   //Debug
   for (int i = 0; i < numCount; i++)
       printf("numbers[%d] = %f\n", i, numbers[i]);

    for (int i = 0; i < opCount; i++)
        printf("operators[%d] = %c\n", i, operators[i]);



    //Output Section
   printf("You Inputed: %s\n", RawIn);
   printf("Answer = %f\n", numbers[numCount-1]);


    //Ending Section
    sleep(10);

    return 0;
}
