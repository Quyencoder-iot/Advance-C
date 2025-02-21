#include <stdio.h>
#include <stdlib.h>

void test1(){
    int array[3];
    for (int i = 0; i < 3; i++){
        printf("address of array[%d]: %p\n", i, (array+i));
    }
    printf("----------------------\n");
}

void test2(){
    int *array = (int*)malloc(3*sizeof(int));
    for (int i = 0; i < 3; i++){
        printf("address of array[%d]: %p\n", i, (array+i));
    }
    printf("----------------------\n");
    free(array);
}

int main(int argc, char const *argv[]){  
    test1();
    test1();
    test2();
    test2();
    return 0;
}
