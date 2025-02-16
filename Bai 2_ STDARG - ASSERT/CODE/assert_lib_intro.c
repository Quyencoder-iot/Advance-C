#include<stdio.h>
#include<assert.h>
int main(){
    int x = 56;
    assert(x==5); // macro kiểm tra điều kiện x =5 nếu không thỏa mãn sẽ báo lỗi và nó sẽ ghi rõ ở file nào và dòng nào để bạn dễ tìm.
    printf("X is: %d",x);
    return 0;
}