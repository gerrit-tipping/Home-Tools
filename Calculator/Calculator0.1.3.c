#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
//functions//


//operator functions//
double add(double a, double b) { if (!isnan(a)&&!isnan(b)){return a + b; }else{return NAN;}

}
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
int OpPrec(char operator, int *BasePrecidince){
    if(operator=='('){
        *BasePrecidince += 100;
        return 0;
    }
    else if(operator==')'){
        *BasePrecidince -= 100;
        return 0;
    }
    else{
        switch(operator)
        {
            case '+': return (1 + *BasePrecidince);
            case '-': return (1 + *BasePrecidince);
            case '*': return (2 + *BasePrecidince);
            case '/': return (2 + *BasePrecidince);

            default:
                printf("Invalid operator: %c\n", operator);
                return 0;
        }
    }
}


//Evaluation Function//
void EvalNode(double LeafNodes[], char OpNodes[], int *LeafCount, int *OpNodesCount, int OpPriority[]){
    int MaxOpPriority = 0;
    if(*LeafCount == *OpNodesCount + 1){
        for(int i=0; i<*OpNodesCount; i++){
            if (OpPriority[i] > MaxOpPriority){
                MaxOpPriority = OpPriority[i];
            }
        }
        while (MaxOpPriority > 0){
            int i=0;
            while(i<*OpNodesCount){
                if (OpPriority[i] == MaxOpPriority){
                    LeafNodes[i]=NodeCalc(LeafNodes[i],LeafNodes[i+1],OpNodes[i]);
                    printf("%f\n", LeafNodes[i]);
                    for(int j=i+1; j<(*LeafCount-1); j++){
                        LeafNodes[j] = LeafNodes[j+1];
                    }
                    for(int j=i; j<(*OpNodesCount-1); j++){
                        OpNodes[j] = OpNodes[j+1];
                        OpPriority[j] = OpPriority[j+1];
                    }
                    (*OpNodesCount)--;
                    (*LeafCount)--;
                }
                else{
                    i++;
                }
            }
            MaxOpPriority--;
        }
    }
}







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
        else if(*p == '('||*p == ')')
        {
            OpNodes[*OpNodesCount] = *p;
            (*OpNodesCount)++;
            p++;
            PrevCharWasOp = true;
        }
        else{
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
    bool WaitEnd=false;
    int ClosingTimer=3;



//Variable Definitions//

    char *SupportedOps[] = {
        "+","-","*","/"
    };

    char RawIn[100];
    double LeafNodes[100];
    double answer;
    char OpNodes[100];
    int BasePrecidince = 0;
    int LeafCount = 0;
    int OpNodesCount = 0;
    int SupportedOpsCount =sizeof(SupportedOps) / sizeof(SupportedOps[0]);
    int OpPriority[100];
//Input//
    printf("Input Data Below\n");
    fgets(RawIn, sizeof(RawIn), stdin);
    RawIn[strcspn(RawIn, "\n")] = '\0';




//Processing//
    PrepNode(RawIn, LeafNodes, OpNodes, &LeafCount, &OpNodesCount);

for (int i = 0; i<OpNodesCount;i++){
    OpPriority[i]=OpPrec(OpNodes[i],&BasePrecidince);
}

for (int i = 0; i<OpNodesCount;i++){
    if(OpNodes[i]=='('||OpNodes[i]==')'){
        for(int j=i+1; j<OpNodesCount;j++){
            OpNodes[j-1]=OpNodes[j];
            OpPriority[j-1]=OpPriority[j];
        }
        OpNodesCount--;
        i--;
    }
}


//Debug//
if (DebugMode==true)
{printf("number of supported operations: %d\n", SupportedOpsCount);
    //Output Section
    printf("You Inputed: %s\n", RawIn);
    printf("OpNodesCount = %d\n", OpNodesCount);
    for (int i = 0; i<OpNodesCount;i++){
        printf("Operator = %c  Priority = %d\n", OpNodes[i], OpPriority[i]);
    }
}

EvalNode(LeafNodes, OpNodes, &LeafCount, &OpNodesCount, OpPriority);
answer=LeafNodes[0];



printf("Answer = %f\n", answer);
//Debug//
   if (DebugMode==true)
   {printf("number of supported operations: %d\n", SupportedOpsCount);
    //Output Section
   printf("You Inputed: %s\n", RawIn);
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
