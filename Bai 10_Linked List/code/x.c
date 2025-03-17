#include <stdio.h>

// Hàm thay đổi giá trị của tham số
void changeValue(int x) {
    x = 10; // Thay đổi giá trị của tham số x
    printf("Trong hàm changeValue: x = %d\n", x);
}

int main() {
    int x = 5;
    printf("Trước khi gọi hàm: x = %d\n", x); // In ra 5

    changeValue(x); // Truyền giá trị của a vào hàm

    printf("Sau khi gọi hàm: x = %d\n", x); // Vẫn in ra 5

    return 0;
}