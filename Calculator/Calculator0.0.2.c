#include <stdio.h>

int main(void) {
    char RawIn[100];
    printf("Input Data Below\n");
    fgets(RawIn, sizeof(RawIn), stdin);
    printf("You Inputed: %s\n", RawIn);
    sleep(10);
    return 0;
}
