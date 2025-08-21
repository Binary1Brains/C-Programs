#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct {
    int size;
    int top;
    float *stack;
} Stack;

void push(float a, Stack* S) {
    S->stack[++(S->top)] = a;
}

float pop(Stack *S) {
    return S->stack[(S->top)--];
}

void arrayconverter(char *exp, char *exp2[], int *c);
int isOperator(char*);
float evaluate(float, float, char*);

int main() {
    Stack s;
    s.size = 100;
    s.stack = (float*)malloc(s.size * sizeof(float));
    s.top = -1;
    if (s.stack == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    char* exp = (char*)malloc(100 * sizeof(char));
    if (exp == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter a postfix expression: ");
    fgets(exp, 100, stdin);
    exp[strcspn(exp, "\n")] = 0;  // Remove newline from input

    int count = 0;
    char* exp2[100];  // Array to store expression tokens
    arrayconverter(exp, exp2, &count);

    // Process the postfix expression
    for (int i = 0; i < count; i++) {
        if (isOperator(exp2[i])) {
            float a = pop(&s);  // Pop the right operand
            float b = pop(&s);  // Pop the left operand
            float result = evaluate(b, a, exp2[i]);  // Apply operator in correct order
            push(result, &s);  // Push the result back to the stack
        } else {
            push(atof(exp2[i]), &s);  // Push the operand to the stack
        }
    }

    // The final result will be the last element in the stack
    printf("Result: %.2f\n", pop(&s));

    // Free dynamically allocated memory
    free(exp);
    free(s.stack);

    return 0;
}

// Function to convert the expression into an array of tokens
void arrayconverter(char *exp, char *exp2[], int *c) {
    char *token;
    int i = 0;
    token = strtok(exp, " \t\n");
    while (token != NULL) {
        exp2[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    *c = i;
}

// Function to check if the character is an operator
int isOperator(char *c) {
    char ch = c[0];
    switch (ch) {
    case '+':
    case '-':
    case '%':
    case '*':
    case '^':
        return 1;  // Return true for operators
    default:
        return 0;  // Return false for non-operators
    }
}

// Function to evaluate an operation with two operands
float evaluate(float b, float a, char *operator) {
    switch (operator[0]) {
    case '+':
        return b + a;  // Addition
    case '-':
        return b - a;  // Subtraction
    case '%':
        return (int)b % (int)a;  // Modulo operation (integer)
    case '*':
        return b * a;  // Multiplication
    case '^':
        return pow(b, a);  // Exponentiation
    default:
        return 0.0f;  // Return 0 for unsupported operators
    }
}
