#include <stdio.h>

#define CREAT_FUNC(name_func, content1, content2)     \
void name_func()                                      \
{                                                     \
    printf(content1);                                 \
    printf(content2);                                 \
}
CREAT_FUNC(sv1, "Trinh, "," sdt:09xxx\n");
CREAT_FUNC(sv2, "Duc, ","08xxx\n");
CREAT_FUNC(sv3, "Nam, ","06xxx\n");
//## : dùng nối chuỗi
//#: dùng chuyển đoạn văn bản thành chuỗi
// printf : chỉ in ra chuỗi, nên nếu không phải chuỗi nó sẽ báo lỗi.
#define CONCAT(a,b) a##b
#define CREATE_STRING(content) printf(#content) // định nghĩa lại hàm printf

// Bài toán tỉnh tổng khi số lượng tham số chưa xác định là bao nhiêu
// Note1 : dùng variadic ..., __VA_ARGS__ gọi ra hoặc hiển thị tham số ...
// Note 2: For loop chỉ dung khi biết rõ số lượng tham số, While dùng khi chưa rõ số lượng tham số
// ý tưởng trong các tham số cho thêm số  0 để kết thúc vòng lặp while này, khi arr[] !=0 thì cộng dồn vào tổng, kết thúc khi arr[]=0 
#define tong(...)                  \  
int arr[] = {__VA_ARGS__, 0};      \
int sum = 0;                       \
int i =0;                          \
while(arr[i] != 0)                 \
{                                  \
sum += arr[i];                     \
i++;                               \
}                                  \
printf("\n tong la %d\n", sum);


int main()
{
    sv1();
    sv2();
    sv3();
    int ab = 369;
    printf("value %d\n", CONCAT(a,b));
    CREATE_STRING(hello world);
    tong(1,2,3,4,6,9);
    #define data 30
    printf("data la: %d\n", data);
    #undef data
    #define data 60
    printf("data moi la: %d\n", data);

    return 0;
}