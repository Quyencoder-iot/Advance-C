// Vung nhớ stack lưu biến cục bộ, và tham số truyền vào hàm. hoạt đông theo nguyên tắc LIFO.
#include <stdio.h>

void test()
{
    int test = 0; //stack
    test = 5; // stack
    printf("test: %d\n",test);
}
int sum(int a, int b) // stack : a,b,c
{
    int c = a + b;
    printf("sum: %d\n",c);
    return c;
}

int main() {

    sum(3,5);
    /*
        0x01
        0x02
        0x02
        0x03
    */
   test();
   /*
    int test = 0; // 0x01
   */

    return 0;
}



