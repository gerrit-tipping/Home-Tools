#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>

//functions//


//operator functions//
double add(double a, double b) { return a + b; }
double sub(double a, double b) { return a - b; }


//node processing function//
double CalculateNode(char *DataIn){
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

    //Data Processing Section

    char *p = DataIn;

    bool PrevCharWasOp =NULL;
    int ReadPosition = 0;
    while (*p != '\0') {

        if (isdigit(*p) || *p == '.' || (PrevCharWasOp == true && *p=='-')||ReadPosition == 0) {
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
        ReadPosition = ReadPosition+1;
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

        if (operation != NULL){
            numbers[i+1]= operation(a, b);
        }

    }
    return numbers[numCount-1];
}






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
    double answer;
    char operators[100];

    int numCount = 0;
    int opCount = 0;
    int SupportedOpsCount =sizeof(SupportedOps) / sizeof(SupportedOps[0]);

//Input//
    printf("Input Data Below\n");
    fgets(RawIn, sizeof(RawIn), stdin);





//Processing//
    answer = CalculateNode(RawIn);




//Debug//
   if (DebugMode==true)
   {printf("number of supported operations: %d\n", SupportedOpsCount);
    //Output Section
   printf("You Inputed: %s\n", RawIn);
   printf("Answer = %f\n", answer);
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
