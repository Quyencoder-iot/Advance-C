#include <stdio.h>
typedef struct 
{
    int x;
    int y;
} Point_Data;

Point_Data p1 = {5,0}; //p1, x, y : data
Point_Data p2 = {0,0}; //p2,x, y: BSS
Point_Data p3;         //p3,x, y: BSS
int a = 0; // BSS
int b;      //bss
int *ptr; // bss
char *str = "hello world";
// str: Data

static int global = 0; //BSS
static int global_2; //BSS
static Point_Data p4 = {0,0}; //p4, x, y :BSS
const int e = 0; // text

void test()
{
    int a = 10; // bss , do đã được khởi tạo ở biến toàn cuc
    static int local = 0; // BSS
    static int local_2;  // BSS
}
int main() {

    printf("a: %d\n", a);
    printf("global: %d\n", global); 
   //str[1] = 'a'; 
    printf("chuoi: %s\n", str);  
    return 0;
}



