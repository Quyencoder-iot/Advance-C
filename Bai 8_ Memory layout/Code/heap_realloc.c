#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int main() {
    int *arr_calloc;
    int size = 6;
    //Note kiểu khai báo: *ptr: dấu * đứng trươc => nghĩa là ptr là con trỏ.
    //Còn khai báo : datatype* : dấu * đằng trước kiểu dữ liệu => ép kiểu dữ liệu này cho con trỏ void.
    // Dùng malloc() cấp phát vùng nhớ.
    // Chú ý dòng lệnh dưới, con trỏ ptr nằm phân vùng data, bss hoặc stack tùy cách khai báo. nhưng vùng nhớ nó trỏ đến nằm phân vùng heap
   uint16_t *ptr = (uint16_t*)malloc(size * sizeof(uint16_t)); //0x01, 0x02... /heap
   ptr[2] = 30;
    
   for(size_t i=0; i< size; i++){

        printf("dia chi ptr %d : %p, value %d \n",i, ptr+i, *(ptr+i));
        
    }
    //realloc() thay đổi kích thước vùng nhớ mà malloc() đã cấp phát mà không thay đổi giá trị trong vùng nhớ cũ đó.
    // phải ép kiêu uint16_t cùng kiểu dữ liệu trong vùng nhớ cũ.
   ptr = (uint16_t*)realloc(ptr,10*sizeof(uint16_t));
   printf("Vùng nhớ mới cấp phat lên 10* sizeof(uint16_t)\n");

   for(size_t i=0; i< 10; i++){
    printf("dia chi ptr %d : %p, value %d \n",i, ptr+i, *(ptr+i));   
}

    // Sử dụng calloc
    arr_calloc = (int*)calloc(size, sizeof(int));

    // Giải phóng bộ nhớ
    free(ptr);
    free(arr_calloc);

    return 0;
}
