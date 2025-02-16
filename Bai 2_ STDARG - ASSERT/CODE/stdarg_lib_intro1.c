// Creat Ham hien thi danh sach doi so bat ki luc them vao
#include <stdio.h>
#include <stdarg.h>

void display(int count, ...) {   // ham hien danh sach tham số, tham so 1 = số phần tử của danh sách
    va_list args;                // tạo danh sách tham số args
    va_start(args, count);       // bắt đầu tạo danh sách, tham số đầu = số lượng đối số.
    printf("value 1 la %d\n", va_arg(args,int));
    printf("value 2 la %d\n", va_arg(args,double));
    printf("value 3 la %d\n", va_arg(args,int));
    printf("value 4 la %d\n", va_arg(args,char*)); // Có thể ép kiểu dữ liệu bất kỳ cho từng tham số, tuy nhiên kết quả in ra sai nếu không đúng kiểu của nó
    printf("value 51 la %d\n", va_arg(args,char*));

    for (int i = 0; i < count; i++) {
        printf("Value at %d: %d\n", i, va_arg(args,int)); // 1st %d = i, 2rd %d = va_args(args,int)
    }
    va_end(args);
}

int main()
{
    display(5, 5, 8, 15, 10, 13); // tham số 1 =5 : là so luong tham số thêm vào, 5...13: lần lượt là các tham số mới.

    // khi ghi vao danh sach doi so stdarg se cap phap vung nho cho tung doi so. vi du
    // 5: 0x00 -> 0x07
    // 8: 0x07 -> 0x0F
    // Khi goi va_arg : no se truy cap tung vung nho de lay ra gia tri doi so.
    return 0;
}
