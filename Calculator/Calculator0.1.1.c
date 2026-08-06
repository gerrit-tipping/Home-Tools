#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
//functions//


//operator functions//
double add(double a, double b) { if (!isnan(a)&&!isnan(b)){return a + b; }else{return NAN;}}
double sub(double a, double b) { if (!isnan(a)&&!isnan(b)){return a - b; }else{return NAN;}}
double mul(double a, double b) { if (!isnan(a)&&!isnan(b)){return a * b; }else{return NAN;}}
double ddiv(double a, double b) { if (!isnan(a)&&!isnan(b)&&b!=0){return a / b; }else{return NAN;}}


//operation execution//
double NodeCalc(double a, double b, char operator)
{
    switch(operator)
    {
        case '+': return add(a,b);
        case '-': return sub(a,b);
        case '*': return mul(a,b);
        case '/': return ddiv(a,b);

        default:
            printf("Invalid operator: %c\n", operator);
            return 0;
    }
}


// Operator precidence //(BODMAS)
int OpPrec(char operator){
    switch(operator)
    {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;

        default:
            printf("Invalid operator: %c\n", operator);
            return 0;
    }
}


//evaluation//
//evaluate left to right going down precidence








//node prepping function//
void PrepNode(char *DataIn, double LeafNodes[], char OpNodes[], int *LeafCount, int *OpNodesCount){
    //Variable Definitions//


    //Data Processing Section

    char *p = DataIn;

    bool PrevCharWasOp =false;
    int ReadPosition = 0;
    while (*p != '\0') {

        if (isdigit(*p) || *p == '.' || (PrevCharWasOp == true && *p=='-')||(ReadPosition == 0&& *p=='-')) {
            char *end;
            LeafNodes[*LeafCount] = strtod(p, &end);
            (*LeafCount)++;
            p = end;
            PrevCharWasOp = false;
        }
        else {
            OpNodes[*OpNodesCount] = *p;
            (*OpNodesCount)++;
            p++;
            PrevCharWasOp = true;
        }
        ReadPosition = ReadPosition+1;
    }
    return;
}






//main function//
int main(void) {
    //Settings//
    bool DebugMode=true;
    bool KeypressEnd=true;
    bool WaitEnd=true;
    int ClosingTimer=3;



//Variable Definitions//

    char *SupportedOps[] = {
        "+","-","*","/"
    };

    char RawIn[100];
    double LeafNodes[100];
    double answer;
    char OpNodes[100];

    int LeafCount = 0;
    int OpNodesCount = 0;
    int SupportedOpsCount =sizeof(SupportedOps) / sizeof(SupportedOps[0]);
    int OpPriority[100];
//Input//
    printf("Input Data Below\n");
    fgets(RawIn, sizeof(RawIn), stdin);





//Processing//
    PrepNode(RawIn, LeafNodes, OpNodes, &LeafCount, &OpNodesCount);

for (int i = 0; i<OpNodesCount;i++){
    OpPriority[i]=OpPrec(OpNodes[i]);
}




//Debug//
   if (DebugMode==true)
   {printf("number of supported operations: %d\n", SupportedOpsCount);
    //Output Section
   printf("You Inputed: %s\n", RawIn);
   printf("Answer = %f\n", answer);
   printf("OpNodesCount = %d\n", OpNodesCount);
   for (int i = 0; i<OpNodesCount;i++){
       printf("Operator = %c  Priority = %d\n", OpNodes[i], OpPriority[i]);
   }
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
