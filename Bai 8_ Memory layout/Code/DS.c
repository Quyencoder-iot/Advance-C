#include <stdio.h>
// các biến a,d, var sẽ phân vào phân vùng DS nếu nó được khởi tạo giá trị khác 0
int a = 10;          //DS 0x03...
double d = 20.5;     //DS
static int var = 5;   //DS
int b = 0; // BSS
float c ;   //BSS

void test()
{
    static int local = 10; // DS 
    static int e; //BSS
}


int main(int argc, char const *argv[])
{  
    
    a = 15;
    d = 25.7;
    var = 12;
    printf("a: %d\n", a);
    printf("d: %f\n", d);
    printf("var: %d\n", var);

    return 0;
}
