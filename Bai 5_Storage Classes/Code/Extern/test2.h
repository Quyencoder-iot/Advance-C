// File .h là cac file làm việc ở cấp độ macro, nó sẽ truyền giá trị cụ thể cho biến hoặc hàm
// file header như mục lục liệt kê các biến, hàm sẽ sử dụng cho file.c, trong file.c cụ thể hóa biến hàm này.
// biến extern thường được sử dụng trong các file .h, ít dùng trong các file .c
#ifndef test2_h  // nếu chưa định nghĩa test2.h
#define test2_h  // định nghĩa file test2.h, 2 câu lệnh này tránh tạo trùng file

extern int b;

void display2();

#endif