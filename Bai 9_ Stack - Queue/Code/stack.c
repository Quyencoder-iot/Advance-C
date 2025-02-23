//Stack quản lý dữ liệu theo nguyên lý LIFO : Last in first out.
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    int* items;  // con trỏ items sẽ dùng trỏ đếm vùng nhớ cấp phát động heap, bản chất con trỏ là 1 mảng lưu data
    int size;    // kích thước stack
    int top;     // đỉnh stack, top =-1 : empty stack, top = size-1 : full stack
} Stack; // khai bao stack gồm kích thước size, vi trí hiện tại dữ liệu top, con trỏ items trỏ đến vùng nhớ và lưu dữ liệu.

void initialize( Stack *stack, int size) {  // hàm khởi tạo các giá trị ban đầu cho stack, tham số truyền vào kiểu con trỏ stack, trả lại kiểu void.
    stack->items = (int*) malloc(sizeof(int) * size); // cấp phát vùng nhớ động kích thước = size.
    stack->size = size;
    stack->top = -1;    // top vừa là đỉnh stack, cũng là vị trí hiện tại của dữ liệu.
}

int is_empty( Stack stack) { // kiểm tra stack rỗng
    return stack.top == -1;
}

int is_full( Stack stack) {   // kiểm tra stack đầy
    return stack.top == stack.size - 1;
}
// Thêm phần tử vào stack (Push)
void push( Stack *stack, int value) {  // hàm đẩy giá trị vào đỉnh stack
    if (!is_full(*stack)) {           //  Dùng *stack cho is_full() vì, push khai báo stack là tham số con trỏ, : phép giải tham chiếu trả lại giá trị struct, hàm is_full định nghĩa đối tượng truyền vào là struct 
        stack->items[++stack->top] = value; // vị trí hiện tại là top, ++stack->top : tăng chỉ số top lên 1 trước. stack->items[]: gán mảng con trỏ items ở vị trí top = giá trị phần tử.
    } else {
        printf("Stack đầy\n");
    }
}
// Lấy phần tử ra khỏi stack (Pop)
int pop( Stack *stack) {
    if (!is_empty(*stack)) {
        return stack->items[stack->top--]; //lấy phần tử vị trí top ra và sau đó giảm số đỉnh top đi 1.
    } 
    else {
        printf("Stack rỗng\n");
        return -1;
    }
}
// Xem phần tử ở đỉnh stack (Peek)
int peek( Stack stack) {
    if (!is_empty(stack)) {
        return stack.items[stack.top]; // trả về giá trị data ở đỉnh top 
    } else {
        printf("Stack is empty\n");
        return -1;
    }
}

// Hiển thị toàn bộ stack
void display(struct Stack* stack) {
    if (is_empty(*stack)) {
        printf("Stack rỗng!\n");
        return;
    }
    printf("Nội dung stack (từ đỉnh xuống đáy): ");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d ", stack->items[i]);
    }
    printf("\n");
}

int main() {
    Stack stack1;
    initialize(&stack1, 5); 
    push(&stack1, 10); 
    push(&stack1, 20);
    push(&stack1, 30);
    push(&stack1, 40);
    push(&stack1, 50); // đẩy các phần tử 10,20,30,40,50 vào stack.
    
    display(&stack1);  // hiển thị cả stack
    printf("Top element: %d\n", peek(stack1)); // hiển thị giá trị đỉnh stack

    pop(&stack1); // lấy phần tử đỉnh stack ra
    push(&stack1, 60); // đấy giá trị thay thế vào đỉnh stack.
    
    display(&stack1);
    printf("Top element: %d\n", peek(stack1));
    

    return 0;
}


