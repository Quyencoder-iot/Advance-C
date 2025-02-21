
#include <stdio.h>
int *ptr = NULL;
void CountFunc1() {
    int a = 5;  // 0x0a : STACK (phân vùng trong bộ nhớ)
    printf("a: %d\n", ++a); // Note: ++count thì sẽ + lên trươc khi in ra, còn nếu việt count++ thì nó sẽ thực hiện in trước khi+
}
void CountFunc2() {
    static int count = 5; // 0x09 : BSS
    ptr = &count;
    printf("address: %p, Count: %d\n", ptr, ++count); 
}
void CountFunc3() {
    static int c = 0; // 0x0F : Data

    printf(" c: %d\n", ++c);
}
/*
- Tùy cách khai báo biến mà chương trinh C sẽ cấp cho phân vùng khác nhau (Stack, BSS, Data), mỗi phân vùng lại có 1 đặc điểm riêng
- Nếu biên trong phân vùng Stack thì biến count được cấp địa chỉ trong phân vùng stack. đặc điểm phân vùng này sẽ thu hồi địa chỉ
    ngay sau khi kết thúc hàm. bởi vậy CountFunc1() in ra 3 con 6.
- Nếu dùng static khai báo cho biến, và gán giá trị khác 0 (CountFunc2) thì biến đó sẽ vào phân vung BSS
    Đặc điểm: BSS chỉ thu hồi địa chỉ bộ nhớ sau khi kết thúc toàn bộ chương trinh, hoặc tắt vscode đi nó mới thu hồi. Địa chỉ tồn tại xuyên suốt chương trình
    bởi vậy chương trình in ra là 6,7,8
- Nếu dùng static khai báo và giá trị = 0 thì nó sẽ phân vào phân vùng Data.

*/

int main() {
    CountFunc1();  // In ra "Count: 6"
    CountFunc1();  // In ra "Count: 6"
    CountFunc1();  // In ra "Count: 6"
    printf("\n"); 

    CountFunc2();  // In ra "Count: 6"
    CountFunc2();  // In ra "Count: 7"
    CountFunc2();  // In ra "Count: 8"
    printf("\n"); 

    CountFunc3();  // In ra "Count: 1"
    CountFunc3();  // In ra "Count: 2"
    CountFunc3();  // In ra "Count: 3"

    return 0;
}