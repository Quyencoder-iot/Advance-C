// Ham tinh tong danh sach bat ky
#include <stdio.h>
#include <stdarg.h>

int sum(int count, ...) {
    va_list args; // Tạo danh sách tham số args
    va_start(args, count); // tham số 1 = count = số lượng phần tham số

    int result = 0;
    for (int i = 0; i < count; i++) {
        result += va_arg(args, int);
    }

    va_end(args);

    return result;
}

int main() {
    printf("Sum: %d\n", sum(4, 1, 2, 3, 6));
    return 0;
}
