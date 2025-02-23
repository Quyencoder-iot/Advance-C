#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *items; // mảng lưu trữ giá trị các phần tử
    int size;   // kích thước của hàng đợi
    int front;  // chỉ số phần tử đầu hàng đợi
    int rear;   // chỉ số phần tử cuối hàng đợi
} Queue;

// khởi tạo hàng đợi
void queue_Init(Queue *queue, int size)
{
    queue->items = (int*)malloc(size * sizeof(int)); // cấp phát vùng nhớ động cho mảng items
    queue->size  = size;
    queue->front = queue->rear = -1;
}

// kiểm tra hàng đợi rỗng
int queue_IsEmpty(Queue queue)
{
    return (queue.front == -1);
}

// kiểm tra hàng đợi đầy
int queue_IsFull(Queue queue)
{
    return (queue.rear + 1) % queue.size == queue.front; 
    /*
    Giả sử queue.size = 5, queue.front = 0, queue.rear = 4.
    (4 + 1) % 5 = 0.
    0 == queue.front (vì front = 0), nên hàng đợi đầy.
    Hàm trả về 1.
    Trường hợp 2: Hàng đợi đầy (vị trí vòng)
    Giả sử queue.size = 5, queue.front = 2, queue.rear = 1.
    (1 + 1) % 5 = 2.
    2 == queue.front (vì front = 2), nên hàng đợi đầy.
    Hàm trả về 1.
    
    */
}

// thêm phần tử vào cuối hàng đợi
void enqueue(Queue *queue, int data)
{
    if (queue_IsFull(*queue))
    {
        // nếu queue đầy thì không cho thêm phần tử vào
        printf("Hàng đợi đầy!\n");
    }
    else
    {
        if (queue->front == -1)
        {
            queue->front = queue->rear = 0;
        }
        else
        {
            queue->rear = (queue->rear + 1) % queue->size;
            /*
            Phép toán module % : chia lấy dư => giúp rear quay vòng
            giả sử size = 2
            Thêm phần tử đầu tiên:
            rear = (-1 + 1) % 2 = 0 % 2 = 0
            Phần tử được thêm vào vị trí 0.
            Thêm phần tử thứ 2:
            rear = (0 + 1) % 2 = 1 % 2 = 1
            Phần tử được thêm vào vị trí 1.
            Thêm phần tử thứ ba:
            rear = (1 + 1) % 2 = 2 % 2 = 0
            phần tử thứ 3 sẽ quay lại vị trí 0: đầu mảng
            */
        }
        queue->items[queue->rear] = data;
        printf("Enqueued %d\n", data);
    }
}

#define QUEUE_EMPTY -1

// xóa phần tử từ đầu hàng đợi
int dequeue(Queue *queue)
{
    if (queue_IsEmpty(*queue))
    {
        // nếu queue rỗng thì không cho xóa
        printf("Hàng đợi rỗng\n");
        return QUEUE_EMPTY;
    }
    else
    {
        int dequeue_value = queue->items[queue->front]; // gán giá trị phần tử vào biến trung gian trước khi xóa
        if (queue->front == queue->rear && (queue->rear ==  queue->size - 1)) //kiểm tra nếu còn 1 phần tử cuối cùng
        {
            queue->front = queue->rear = -1; // reset về trạng thái queue rỗng
        }
        else
        {
            queue->front = (queue->front + 1) % queue->size; // Dùng phép toán module giúp front quay vòng. nếu xóa hết phần tử front cũng quay về 0 : vị trí đầu mảng
        }
        return dequeue_value;
    }
}

// lấy giá trị của phần tử đứng đầu hàng đợi (front)
int front(Queue queue)
{
    if (queue_IsEmpty(queue))
    {
        printf("Queue is empty\n");
        return QUEUE_EMPTY;
    }
    else
    {
        return queue.items[queue.front];
    }
}

// lấy giá trị của phần tử đứng cuối hàng đợi (rear)
int rear(Queue queue)
{
    if (queue_IsEmpty(queue))
    {
        printf("Queue is empty\n");
        return QUEUE_EMPTY;
    }
    else
    {
        return queue.items[queue.rear];
    }
}

// Hiển thị các phần tử
void display(Queue q)
{
    if (queue_IsEmpty(q))
    {
        printf("Hàng đợi rỗng\n");
        return;
    }
    printf("Hàng đợi: ");
    int i = q.front;

    while (1) // do front, rear lúc này có giá trị quay vòng nên phải dùng vòng lăp while.
    {
        printf("%d ", q.items[i]);
        if (i == q.rear) break; // điều kiện để thoát khỏi vòng lặp vô tận
        i = (i + 1) % q.size; // phép toán module % giúp quay vòng giá trị i.
    }
    printf("\n");
}


int main(int argc, char const *argv[])
{
    Queue queue;
   
    queue_Init(&queue, 5);

    enqueue(&queue, 3);
    enqueue(&queue, 6);
    enqueue(&queue, 9);
    enqueue(&queue, 33);
    enqueue(&queue, 66);

    display(queue);

    printf("Front element: %d\n", front(queue));
    printf("Rear element: %d\n", rear(queue));

    printf("Dequeued %d\n", dequeue(&queue));
    // printf("Dequeued %d\n", dequeue(&queue));
    // printf("Dequeued %d\n", dequeue(&queue));
    // printf("Dequeued %d\n", dequeue(&queue));

    display(queue);

    enqueue(&queue, 50);
    display(queue);

    printf("Front element: %d\n", front(queue));
    printf("Rear element: %d\n", rear(queue));

    return 0;
}
