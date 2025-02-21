#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int main() {
    int *arr_calloc;
    int size = 6;

    // Sử dụng malloc
    //malloc cap phat cho con tro ptr vung nho 0x01, 0x02,0x03... có kích thước = 5 * sizeof(uint16_t)
    //Do ham malloc tra về kiểu void nên phải ép kiểu uint16_t* để đọc được giá trị lưu trong vùng nhớ đó.
    //con trỏ ptr nằm phân vùng data, bss hoặc stack tùy cách khai báo. nhưng vùng nhớ nó trỏ đến nằm phân vùng heap

   uint16_t *ptr = (uint16_t*)malloc(size * sizeof(uint16_t)); //0x01, 0x02... /heap
   ptr[2] = 30;
    
   for(size_t i=0; i< size; i++){

        printf("dia chi ptr %d : %p, value %d \n",i, ptr+i, *(ptr+i));
        
    }
   
    // Sử dụng calloc
    arr_calloc = (int*)calloc(size, sizeof(int));

    // Giải phóng bộ nhớ
    free(ptr); // sau khi sử dụng vùng nhớ xong phải thu hồi lại vùng nhớ tránh để đó sẽ bị leak
    free(arr_calloc);

    return 0;
}
