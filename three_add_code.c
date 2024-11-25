/*
write a  'C' program to generate the 3 address code.
step 1 :- Begin the program 
step 2 :-   The expression reads from the file using file pointer
step 3 :-   Each string is read and total no of string is calculated
step 4 :-   Each string compared with an operater : if any operator is 
        seen then the previous string and next string are concatenated
        and stored in first temp variable and threee address code expression is printed.

step 5 :-   Suppose if another operand is seen then the first temp variable is concatenated to the next string using the operator and the exp is printed

step 6 :-   The final temp  variable is replaced to the left operand value.

step7 :-    End the program.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

void generateThreeAddressCode(char *expr) {
    int tempVarCount = 1;
    char opsStack[256];
    char operandStack[256][256];
    int opsTop = -1, operandTop = -1;
    char finalResult[256] = {0};
    
    char varName[256] = {0};
    int varIndex = 0;
    
    for (int i = 0; i < strlen(expr); i++) {
        if (expr[i] == '=') {
            int j = i - 1;
            while (j >= 0 && isalnum(expr[j])) {
                varName[varIndex++] = expr[j];
                j--;
            }
            varName[varIndex] = '\0';
            strrev(varName); 
            break;
        }
    }

    for (int i = 0; i < strlen(expr); i++) {
        if (expr[i] == ' ') continue;

        if (isalnum(expr[i])) {
            int j = i;
            char currentOperand[256] = {0};
            while (isalnum(expr[j])) {
                strncat(currentOperand, &expr[j], 1);
                j++;
            }
            i = j - 1;
            strcpy(operandStack[++operandTop], currentOperand);
        } 
        else if (expr[i] == '(') {
            opsStack[++opsTop] = expr[i];
        } 
        else if (expr[i] == ')') {
            while (opsTop >= 0 && opsStack[opsTop] != '(') {
                char tempVar[256];
                snprintf(tempVar, 256, "t%d", tempVarCount++);
                printf("%s = %s %c %s\n", tempVar, operandStack[operandTop - 1], opsStack[opsTop], operandStack[operandTop]);
                strcpy(operandStack[operandTop - 1], tempVar);
                opsTop--;
                operandTop--;
            }
            opsTop--; 
        } 
        else if (isOperator(expr[i])) {
            while (opsTop >= 0 && precedence(opsStack[opsTop]) >= precedence(expr[i])) {
                char tempVar[256];
                snprintf(tempVar, 256, "t%d", tempVarCount++);
                printf("%s = %s %c %s\n", tempVar, operandStack[operandTop - 1], opsStack[opsTop], operandStack[operandTop]);
                strcpy(operandStack[operandTop - 1], tempVar);
                opsTop--;
                operandTop--;
            }
            opsStack[++opsTop] = expr[i];
        }
    }

    while (opsTop >= 0) {
        char tempVar[256];
        snprintf(tempVar, 256, "t%d", tempVarCount++);
        printf("%s = %s %c %s\n", tempVar, operandStack[operandTop - 1], opsStack[opsTop], operandStack[operandTop]);
        strcpy(operandStack[operandTop - 1], tempVar);
        opsTop--;
        operandTop--;
    }
    
    strcpy(finalResult, operandStack[operandTop]);
    
    printf("%s = %s\n", varName, finalResult);
}

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("Expression: a = (b+c)/d\n");
        printf("Three-Address Code:\n");
        generateThreeAddressCode("a = (b+c)/d");
        printf("\n");
        return 0;
    }

    char* filePath = argv[1];
    FILE *file;
    char line[256];

    file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        printf("Expression: %s\n", line);
        printf("Three-Address Code:\n");
        generateThreeAddressCode(line);
        printf("\n");
    }

    fclose(file);
    return 0;
}