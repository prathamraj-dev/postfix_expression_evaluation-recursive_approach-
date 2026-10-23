#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int is_operator(const char *t) {
    return strlen(t) == 1 && strchr("+-*/", t[0]) != NULL;
}
double evaluate(char *tokens[], int *pos, int depth) {
    if (*pos < 0) {
        printf("Invalid postfix expression\n");
        exit(1);
    }
    char *token = tokens[*pos];
    (*pos)--;
    /* Base case: operand */
    if (!is_operator(token)) {
        printf("%*soperand %s -> return %s\n", depth * 2, "", token, token);
        return strtod(token, NULL);
    }
    /* Recursive case: operator */
    printf("%*soperator '%s' -> evaluate right operand\n", depth * 2, "", token);
    double b = evaluate(tokens, pos, depth + 1);
    printf("%*soperator '%s' -> evaluate left operand\n", depth * 2, "", token);
    double a = evaluate(tokens, pos, depth + 1);
    double result;
    switch (token[0]) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        default:
            if (b == 0) {
                printf("Division by zero\n");
                exit(1);
            }
            result = a / b;
    }
    printf("%*s%g %s %g = %g\n", depth * 2, "", a, token, b, result);
    return result;
}
int main(void) {
    char *tokens[] = {"5", "6", "2", "+", "*", "12", "4", "/", "-"};
    int n = sizeof(tokens) / sizeof(tokens[0]);
    int pos = n - 1;
    double answer = evaluate(tokens, &pos, 0);
    if (pos != -1) {
        printf("Invalid postfix expression\n");
        return 1;
    }
    printf("\nResult = %g\n", answer);
    return 0;
}