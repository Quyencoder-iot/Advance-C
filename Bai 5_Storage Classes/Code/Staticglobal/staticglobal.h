#ifndef staticglobal_h
#define staticglobal_h

typedef struct {
    float x1;
    float x2;
} Equation;

extern int A,B,C;

void inputCoefficients(int a, int b, int c);

extern float calculateDelta();

void result(Equation *equation);

#endif