#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>

//operator functions//
double add(double a, double b) { return a + b; }
double sub(double a, double b) { return a - b; }

//main function//
int main(void) {
    //Settings//
    bool DebugMode=true;
    bool KeypressEnd=true;
    bool WaitEnd=true;
    int ClosingTimer=5;



//Variable Definitions//

    char *SupportedOps[] = {
        "+","-",
    };

    char RawIn[100];
    double numbers[100];
    double output[100];
    char operators[100];

    int numCount = 0;
    int opCount = 0;
    int SupportedOpsCount =sizeof(SupportedOps) / sizeof(SupportedOps[0]);

//Input//
    printf("Input Data Below\n");
    fgets(RawIn, sizeof(RawIn), stdin);


    //Data Processing Section

    char *p = RawIn;

    for (int i=0; i<SupportedOpsCount;i++){
//add check for first operator before first number
    }
    bool PrevCharWasOp =NULL;
    while (*p != '\0') {


        if (isdigit(*p) || *p == '.' || (PrevCharWasOp == true && *p=='-')) {
            char *end;
            numbers[numCount++] = strtod(p, &end);
            p = end;
            PrevCharWasOp = false;
        }
        else {
            operators[opCount++] = *p;
            p++;
            PrevCharWasOp = true;
        }
    }


//Calculation//
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







//Debug//
   if (DebugMode==true)
   {
   for (int i = 0; i < numCount; i++)
       printf("numbers[%d] = %f\n", i, numbers[i]);

    for (int i = 0; i < opCount; i++)
        printf("operators[%d] = %c\n", i, operators[i]);

    printf("number of supported operations: %d\n", SupportedOpsCount);
    //Output Section
   printf("You Inputed: %s\n", RawIn);
   printf("Answer = %f\n", numbers[numCount-1]);
   }

//End Behavior//
    if (KeypressEnd == true)
    {
   printf("press Enter to close");
    char k[100];
    fgets(k, sizeof(k), stdin); //looks for pressing enter before closing
    }
    if (WaitEnd == true)
    {
        for(int i = 0; i<ClosingTimer; i++)
        {
            int ClosingIn = ClosingTimer-i;
            printf("\rClosing in %d", ClosingIn);
            fflush(stdout);
            sleep(1);
        }
    }
        return 0;
}
