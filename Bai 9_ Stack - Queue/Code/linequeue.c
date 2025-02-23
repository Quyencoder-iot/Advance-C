// Chương trinh viết các hàm thao tác với hàng đợi (kiểm tra hàng đợi đầy, hàng đợi rỗng, thêm vào cuối hàng đợi, xóa phần tử ở đầu hàng đợi, hiển thị các giá trị trong hàng đợi)
// Note: thêm vào queue : rear tăng
// xóa phần tử đầu queue: front tăng(chờ xóa phần tử tiếp)
// hàng đợi có 1 phần tử: front = rear
// queue đầy: rear = size-1
// queue rỗng: rear = front = -1.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int *item;  // con trỏ item có chức năng da dụng trỏ đến địa chỉ vùng nhớ động, lưu mảng giá trị các phần tử. con trỏ 1 cấp vai trò mảng 1 chiều
    int size;   // số lượng phần tử tối đa có thể đưa vào
    int front;  // chỉ số của phần tử đầu hàng đợi
    int rear;   // chỉ số của phần tử cuối hàng đợi
} Queue; //  Như vậy struct hàng đợi sẽ 4 thành viên chính (1.thành viên lưu mảng giá trị,2.kích thước, chỉ số hàng đợi trước, sau)

// khởi tạo hàng đợi
void initialize(Queue *queue, int size) // tham số truyền vào là con trỏ queue và kích thước hàng đợi
{
    queue->size  = size;
    queue->item  = (int*)malloc(size * sizeof(int)); // cấp phát động vùng nhớ cho struct queue, malloc trả về void, nên phải ép kiểu int* cùng kiểu dữ liệu item
    queue->front = queue->rear = -1; // không có phần tử trong hàng đợi front = rear = -1, 
}

// kiểm tra hàng đợi đầy
bool isFull(Queue queue)  //tham số truyền vào là 1 struct queue.
{
    return (queue.rear == queue.size - 1); // queue đầy : rear = size-1 : (kích thước hàng đợi)-1
}

// kiểm tra hàng đợi rỗng
bool isEmpty(Queue queue)
{
    return (queue.front == -1 || queue.front > queue.rear);
}

// thêm phần tử vào cuối hàng đợi
void enqueue(Queue *queue, int data) // note : tham số truyền vào 1. con trỏ queue, 2. data
{
    if (isFull(*queue)) // *queue : giả tham chiếu về kiểu struct, cho khớp với định nghĩa của hàm.
    {
        printf("Hàng đợi đầy!\n");
        return;
    }
    else
    {
        if (queue->front == -1) queue->front = queue->rear = 0; // nếu chưa có phần tử nào front = rear = 0
        else queue->rear++;
        queue->item[queue->rear] = data; // thêm data vào mảng item ở vị trí rear.
        printf("Enqueue data %d\n", data);
    }
}

#define QUEUE_EMPTY -1

// xóa phần tử đầu hàng đợi
// = xóa giá trị tại vị trí front hiện tại, tăng chỉ số front lên 1 (front++), chờ xóa tiếp phần tử.
int dequeue(Queue *queue)
{
    if (isEmpty(*queue)) // kiểm tra hàng đợi rỗng thì không có gì để xóa cả
    {
        printf("Hàng đợi rỗng, không có gì để xóa :))!\n");
        return QUEUE_EMPTY;
    }
    else
    {
        int dequeue_value = queue->item[queue->front]; // gán giá trị phần tử vào biến trung gian trước khi xóa

        queue->item[queue->front] = 0; // xóa giá trị ở phần tử front, front tăng lên 1.

        if (queue->front == queue->rear && queue->rear == queue->size - 1) // kiểm tra nếu xóa đến phần tử cuối cùng thì reset chỉ số front, rear về 1.
        {
            queue->front = queue->rear = -1;
        }
        else
        {
            queue->front++;
        }
        return dequeue_value;
    }
}

void display(Queue queue) // in ra các phần tử trong hàng đợi line
{
    if (isEmpty(queue))
    {
        printf("Hàng đợi rỗng!\n");
    }
    else
    {
        printf("Queue: ");

        for (int i=queue.front; i<=queue.rear; i++)
        {
            printf("%d ", queue.item[i]);
        }
        printf("\n");
    }
}

int front(Queue queue) // đọc giá trị đầu hàng đợi
{
    if (isEmpty(queue))
    {
        printf("Hàng đợi rỗng!\n");
        return QUEUE_EMPTY;
    }
    else
    {
        return queue.item[queue.front];
    }
}

int rear(Queue queue) // đọc giá trị cuối hàng đợi queue
{
    if (isEmpty(queue))
    {
        printf("Hàng đợi rỗng!\n");
        return QUEUE_EMPTY;
    }
    else
    {
        return queue.item[queue.rear];
    }
}

int main(int argc, char const *argv[])
{
    Queue liQueue;

    initialize(&liQueue, 3);

    enqueue(&liQueue, 3);
    enqueue(&liQueue, 6);
    enqueue(&liQueue, 9);
    enqueue(&liQueue, 4);
    enqueue(&liQueue, 5);
    enqueue(&liQueue, 7);

    printf("Front: %d\n", front(liQueue)); // in ra phần tử đầu
    printf("Rear: %d\n", rear(liQueue)); // in ra phần tử cuối

    display(liQueue); // hiển thị toàn bộ phần tử trong queue

    printf("Dequeue %d\n", dequeue(&liQueue)); // lấy 1 phần đầu ra khỏi hàng đợi và in ra giá trị vừa lấy ra
    printf("Dequeue %d\n", dequeue(&liQueue));
    printf("Dequeue %d\n", dequeue(&liQueue));
   
    display(liQueue); // 

    enqueue(&liQueue, 369);
    display(liQueue);

    return 0;
}


