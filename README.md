Bài 01: Compiler process
🔰 Compiler GCC
🔰 The Preprocessor
🔰 Macro
1.1.	Complier GCC
Concept ban đầu
Editor-IDE (Trình soạn thảo code) : vscode, eclipse..
Complier (Trình biên dịch): biên dịch code bạn viết ra ngôn ngữ máy. 
Mỗi IDE dung 1 trình biên dịch => 
Vscode IDE: gcc /g++ , gcc cho C, g++ cho C++, 
Andruino IDE: AVR-gcc









 
Preprocessor: biên dịch file .c, .h, .cpp ra file .i  (trình tiền xử lý)
-	Trên Terminal gõ: gcc -E file.c -o file.i
Complier: biên dịch file .i => .s (file assembly)
-	Terminal: gcc -S file.i -o file.s
Assembler: biên dịch file .s => .o 
-	Terminal: gcc -c file.s -o file.o
File.o này là file máy tính có thể hiểu được. Đối với lập trình vi điều khiển thì khi nó biên dịch từ file.s => file.hex (không phải .o).
Linker: biên dịch gộp tất cả file .o => .exe
Liên kết tất cả file .o trong folder để tạo file .exe
Chú ý nếu có bất kỳ file.c nào chưa biên dịch ra .i =>.s => .o. thì phải biên dịch hết ra .o rồi mới biên dịch hết các files.o ra exe . không sẽ bị báo lỗi
-	Terminal: gcc file1.o file2.o -o main
(Note: tên file exe tự đặt tên bất kỳ main,…)
 
1.2.Preprocessor (.c, .h => .i). đặc điểm file .i.
Máy build các file .c, .h (#include header, Expand macro, delete comment) sang file .i
Đặc điểm quá trình Preprocessor
-	copy toàn bộ mã nguồn viện stdio.h, test.c vào file .i, 
-	chú thích sẽ bị xóa trong file .i
-	các cái định nghĩa trong hàm #define sẽ được thay trực tiếp vào mảng array hoặc chuỗi string…
-	hàm và biến thông thường sẽ được giữ nguyên.
-	Có thể vào file .i để rà soát lỗi các lệnh viết sai.
Kết quả sau complier: từ line 1592 lên phía trên là toàn bộ mã nguồn copy từ thư viện stdio.h. thư viện này là thư viện chuẩn của vscode đã viết sẵn cho một số hàm và biến khai báo trong đó.
 
1.3Macro: 
Là các chỉ thị - khai báo được xử lý ở quá trình tiền xử lý ( Preprocessor-tạo file .i).. Chú ý: sau macro không có dấu “;” cuối dòng.
Macro để xử lý công việc ở tầm vĩ mô, không cụ thể hóa. Macro được xử lý ở quá trình tiền xử lý, biên dịch và tách ra các công việc sẽ được thực hiện trong file .i.
Ví dụ: Lập trình cùng lúc cho 3 vi điều khiển ESP32, Atmega 8, STM32. Có thể sử dụng các Macro điều kiện #if, #else, #endif. Để lựa chọn đoạn code nào lập trình cho mỗi vi điều khiển ở trên. Điều kiện cho 1 vi khiển thỏa mãn thì chương trình chỉ biên dịch đoạn code của vi điều khiển đó, các đoạn code vi điều khiển khác bị ẩn đi.
Ví dụ 2: Dùng Macro #define để định nghịa lại và tạo ra nhiều hàm giống nhau về cấu trúc, chỉ khác tên và nội dụng.
Ví dụ 3: Dùng Macro # variadic để viết tính toán khi số lượng tham số không không cố đinh, và có thể tùy biến.
Sau đây là các nhóm Macro chính.
1.	#include
2.	#define
3.	#undef
4.	#if, #elif, #else, #endif (if, else if)
5.	#ifdef, #ifndef (macro define)
6.	Toán tử
-	## Nối chuỗi
-	# Chuẩn hóa đoạn văn bản thành chuỗi
-	Variadic:
+ … : Đại diện cho danh sách đối số không xác định
+ _VA_ARGS_ : Hiển thị ra danh sách các đối số đó
1.#include : Chèn một đoạn mã nguồn vào file chương trình. Có 2 loại
#include<stdio.h> : trong dấu ngoặc nhọn<>: dung cho thư viện chuẩn cài sẵn trong vscode. Complier sẽ tìm kiếm file nào có tên stdio.h trong thư mục cài đặt của vscode.
Trong file .h sẽ khải báo các nhãn mà không khai báo biến cụ thể, nếu khai báo biến cụ thể, chương trình sẽ bị lỗi.
#include”test.c”: Trong đấu ngoặc kép “”. Complier sẽ tìm kiếm file có tên test.c trong thư mục viết code hiện tại.
2.#define : Dùng định nghĩa lại hằng số, Hàm, hoặc bất kỳ đoạn văn bản nào. Nếu bạn dự định viết nhiều hàm giống nhau,lặp lại nhiều lần. dung macro #define để định nghĩa lại hàm đó cho gọn. thông tin gồm (tên hàm, tham số 1, tham số 2, …)
Đặc điểm: sau khi build ra file .i. Tất cả các tham số trong #define được truyền thẳng vào array, string, hoặc hàm. Và macro #define cũng sẽ bị xóa.
#define cho 1 hàm nhiều dòng thì phải dung thêm dẫu “\” cuối mỗi dòng trừ dòng cuối cùng. Để complier hiểu rằng cái này define những line nào trong hàm.
#include <stdio.h>

#define CREAT_FUNC(name_func, content1, content2)     \
void name_func()                                     \
{                                                    \
    printf(content1);                                 \
    printf(content2);                                \
}
CREAT_FUNC(sv1, "Trinh, "," sdt:09xxx\n");
CREAT_FUNC(sv2, "Duc, ","08xxx\n");
CREAT_FUNC(sv3, "Nam, ","06xxx\n");

int main()
{
    sv1();
    sv2();
    sv3();
    return 0;
}

Output
[Running] cd "e:\3.ELECTRONIC\.HALA-EMBBED PROGRAMMING_GOOD\C & C++ ADVANCE\EXCERCISE\Bai 1 Complier-Macro\" && gcc EX1.c -o EX1 && "e:\3.ELECTRONIC\.HALA-EMBBED PROGRAMMING_GOOD\C & C++ ADVANCE\EXCERCISE\Bai 1 Complier-Macro\"EX1
Trinh,  sdt:09xxx
Duc, 08xxx
Nam, 06xxx

[Done] exited with code=0 in 0.486 seconds

Sau khi complier ra file .i
Hàm define sẽ không còn xuất hiện, toàn bộ tham số truyền vào hàm.
  

Variadic:
+ … : Đại diện cho danh sách đối số không xác định.
+ _VA_ARGS_ : Hiển thị hoặc gọi ra  danh sách các đối số (…)
Ví dụ làm bài toán tính tổng các số chưa xác định.
Dùng vòng lặp For khi xác định được số lượng tham số, Dùng vòng lặp WHILE khi không xác định được số lượng tham số. nhưng cần đặt điều kiện để kết thúc vòng lặp WHILE.
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
    return 0;
}

Output
EX1.c:22:36: warning: backslash and newline separated by space
   22 | #define tong(...)                  \
      |                                     
Trinh,  sdt:09xxx
Duc, 08xxx
Nam, 06xxx
value 369
hello world
 tong la 25

[Done] exited with code=0 in 0.647 seconds

 
Macro #undef : hủy định nghĩa trước đó của 1 #define.
Khi bạn muốn dung một tên nào đó nhiều lần để định nghĩa cho nhiều hằng số, hàm… thì #undef sau đó #define lại dung lại tên đó.
   #define data 30
    printf("data la: %d\n", data);
    #undef data
    #define data 60
    printf("data moi la: %d\n", data);

output
data la: 30
data moi la: 60

[Done] exited with code=0 in 0.667 seconds


Macro: #if, #elseif, #else, #endif : chỉ thị biên dịch có điều kiện. Lựa chọn làm việc với nhiều vi điểu khiển, nhiều đoạn mã khác nhau, nhiều hàm khác nhau. Nó khác với các hàm (if, elseif, else) thông thường.
-	Nó dung để kiểm tra macro
-	Vì là Macro nên nó xảy ra ở quá trình tiền xử lý preprocess
-	Macro #if, #else, # elseif phải có #endif.
Còn các điều kiện (if, else, elseif) thông thường: để kiểm tra một biến hoặc 1 thuật toán nào đó. Và nó xảy ra trong khi trương trình chạy.
Ví dụ: thao tác với 3 con vi điều khiển khác nhau stm32, esp32, atmega8 với 3 mã nguồn khác nhau. Bạn không muốn viết 3 chương trình với 3 mã nguồn khác nhau. Mà chỉ muốn viết 1 chương trình chạy được cho cả 3 vi điều khiển.
Ideal : Gán mỗi vi điều khiển 1 ID, dùng macro #if … # endif và 1 biến chỉ thị để chọn vi điều khiển làm việc. khi đúng id thì chỉ đoạn code liên quan đến vi điều khiển đó sáng và sẽ được biên dịch, các đoạn code vi điều khiển khác sẽ bị ẩn và không được biên dịch.
define STM32 0   //tạo id cho vi dieu khien stm32 =0
#define ATMEGA 1
#define PIC 2

#define MCU STM32  // tạo biến mcu để chọn vxl

#if MCU == STM32
void daoTrangThaiDen(Ports port, Pins pin, Status status)
{}  
#elif MCU == ATMEGA
void daoTrangThaiDen(Pins pin, Status status)
{}

#endif

Có thể thấy dưới đây: khi MCU = STM32 thì đoạn mã cho vxl này sáng lên, trong khi code của atmega bị ẩn đi. Khi biên dịch ra file .i thì chỉ code của stm32 được copy sang file .i.
  

Full code chọn vi điều khiển
#include <stdio.h>

typedef enum
{
    GPIOA,
    GPIOB,
    GPIOC
} Ports;

typedef enum
{
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
} Pins;

typedef enum
{
    HIGH,
    LOW
} Status;

#define STM32 0
#define ATMEGA 1
#define PIC 2

#define MCU STM32

#if MCU == STM32
void daoTrangThaiDen(Ports port, Pins pin, Status status)
{
    if (status == HIGH)
    {
        HAL_GPIO_WritePin(port, pin, LOW);
    }
    else
    {
        HAL_GPIO_WritePin(port, pin, HIGH);
    }  
}
#elif MCU == ATMEGA
void daoTrangThaiDen(Pins pin, Status status)
{
    if (status == HIGH)
    {
        digitalWrite(pin, LOW);
    }
    else
    {
        digitalWrite(pin, HIGH);
    }  
}

#endif

void delay(int ms)
{
}
int main()
{
    while(1)
    {
        daoTrangThaiDen(GPIOA,13,HIGH);
        delay(1000);
    }
    return 0;
}

 
