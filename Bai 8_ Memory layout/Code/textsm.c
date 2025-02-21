//Text Segment : Chỉ Đọc, thực thi, không được ghi vào
#include <stdio.h>

const int a = 10;       // phân vùng text segment
char arr[] = "Hello";   // text segment
char *arr1 = "Hello";   // text segment
int b = 0;
int *ptr = &b;

int main() {
   // Tất Các câu lệnh thưc thi trong main sẽ phân vào text segment.
   // Con trỏ PC sẽ tro đến lần lượt từng câu lệnh để thực thi

    printf("a: %d\n", a); 

    arr[3] = 'W';
    printf("arr: %s", arr); 

    arr1[3] = 'E';
    printf("arr1: %s", arr1);

    
    return 0;
}
