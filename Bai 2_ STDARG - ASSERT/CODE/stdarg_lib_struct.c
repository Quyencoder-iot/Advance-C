// Prog tạo ra 1 struct Data, lấy struct đó làm tham số cho va_list va in ra danh sách struct đó với số lượng tùy chọn

#include <stdio.h>
#include <stdarg.h>

typedef struct Data
{
    int x;
    double y;
} Data;         //Tao Struct Data 2 thành vien x,y co kieu khac nhau int, double. 

void display(int count, ...) {

    va_list args; // tạo danh sách args

    va_start(args, count); // Bắt đầu tạo danh sách, tham số 1 = count = số lượng tham số thêm vào.

    int result = 0;

    for (int i = 0; i < count; i++)
    {
        Data tmp = va_arg(args,Data); // Tạo các tham số có kiểu Data và gán vào biến tmp để in ra.
        printf("Data.x at %d is: %d\n", i,tmp.x); //1st %d = i, 2rd %d =tmp.x
        printf("Data.y at %d is: %f\n", i,tmp.y);
    }
   

    va_end(args);
}

int main() {

    display(3, (Data){2,5.0} , (Data){10,57.0}, (Data){29,36.0});
    return 0;
}
