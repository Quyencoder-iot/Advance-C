// File .h là cac file làm việc ở cấp độ macro, nó sẽ truyền giá trị cụ thể cho biến hoặc hàm
// file header như mục lục liệt kê các biến, hàm sẽ sử dụng cho file.c, trong file.c cụ thể hóa biến hàm này.
// biến extern thường được sử dụng trong các file .h, ít dùng trong các file .c
#ifndef test1_h
#define test1_h

extern int a; // khai báo extern khi muốn biến đó dùng chung cho các file.

void display1();

#endif