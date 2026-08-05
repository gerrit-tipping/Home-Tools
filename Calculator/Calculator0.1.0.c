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
double mul(double a, double b) { return a * b; }
double ddiv(double a, double b) { return a / b; }


//calculate function//
double NodeCalc(double a, double b, char operator){
        double (*operation)(double, double) =NULL;
        switch (operator) {
            case '+': operation = add; break;
            case '-': operation = sub; break;
            case '*': operation = mul; break;
            case '/': operation = ddiv; break;
            default:
                printf("Invalid operator: %c\n", operator);
                return 1;
        }

        if (operation != NULL){
            return operation(a, b);
        }
}


//prepare input//
char *InputPrep(char *Input) {
    int InputLength = strlen(Input);
    char *ProcessedInput = malloc(InputLength + 3);
    ProcessedInput[0] = '(';
    for (int i=0; i < InputLength; i++){
        ProcessedInput[i + 1] = Input[i];
        }
    ProcessedInput[InputLength + 1] = ')';
    ProcessedInput[InputLength + 2] = '\0';
    return ProcessedInput;
}




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

    bool PrevCharWasOp =false;
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
    if (numCount>0)
    {
    return numbers[numCount-1];
    }
    else{
        return 0;
    }
}



//tree definition things//
typedef struct Node {
    char text[256];

    struct Node *child;  // first child layer
    struct Node *next;   // next node at same layer

} Node;



Node *createNode()
{
    Node *node = malloc(sizeof(Node));

    node->text[0] = '\0';
    node->child = NULL;
    node->next = NULL;

    return node;
}



void addCharacter(Node *node, char c)
{
    int len = strlen(node->text);

    node->text[len] = c;
    node->text[len + 1] = '\0';
}



void addChild(Node *parent, Node *child)
{
    if (parent->child == NULL)
    {
        parent->child = child;
    }
    else
    {
        Node *current = parent->child;

        while (current->next)
            current = current->next;

        current->next = child;
    }
}



Node *parse(char *input)
{
    Node *root = createNode();

    Node *stack[1024];

    int top = 0;

    stack[top] = root;


    for (int i = 0; input[i] != '\0'; i++)
    {
        char c = input[i];


        if (c == '(')
        {
            Node *child = createNode();

            addChild(stack[top], child);

            top++;

            stack[top] = child;
        }


        else if (c == ')')
        {
            if (top > 0)
                top--;
        }


        else
        {
            addCharacter(stack[top], c);
        }
    }


    return root;
}



void printTree(Node *node, int depth)
{
    while (node)
    {
        for (int i = 0; i < depth; i++)
            printf("  ");

        printf("%s\n", node->text);


        if (node->child)
            printTree(node->child, depth + 1);


        node = node->next;
    }
}



void freeTree(Node *node)
{
    while (node)
    {
        Node *next = node->next;

        freeTree(node->child);

        free(node);

        node = next;
    }
}





//main function//
int main(void) {
    //Settings//
    bool DebugMode=true;
    bool KeypressEnd=true;
    bool WaitEnd=true;
    int ClosingTimer=5;



    //Variable Definitions//

    char *SupportedOps[] = {"+","-",};

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
    char *CookedIn = InputPrep(RawIn);


    //Processing//
    Node *tree = parse(CookedIn);





    answer = 0;                                                                                                                                    //add tree evaluator function







    //Debug//
    if (DebugMode==true)
    {printf("number of supported operations: %d\n", SupportedOpsCount);
        //Output Section
        printf("You Inputed: %s\n", RawIn);
        printf("Answer = %f\n", answer);
        printf("Tree:\n\n");
        printTree(tree, 0);
    }

    //End Behavior//
        freeTree(tree);
        free(CookedIn);
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
