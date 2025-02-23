#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Định nghĩa cấu trúc cho một phần tử trong priority queue
typedef struct {
    int data;      // Dữ liệu của phần tử
    int priority;  // Mức độ ưu tiên
} Element;

// Định nghĩa cấu trúc cho priority queue
typedef struct {
    Element elements[MAX_SIZE];
    int size;
} PriorityQueue;

// Khởi tạo priority queue
void init(PriorityQueue *pq) {
    pq->size = 0;
}

// Hàm hoán đổi hai phần tử
void swap(Element *a, Element *b) { // khai báo tham số là con trỏ nên tham số truyền vào là địa chỉ
    Element temp = *a; // phép giải tham chiếu, biến temp gán bằng giá trị, con trỏ a trỏ tới.
    *a = *b;
    *b = temp;
}

// Hàm heapify để duy trì tính chất min-heap
void heapify(PriorityQueue *pq, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < pq->size && pq->elements[left].priority < pq->elements[smallest].priority) {
        smallest = left;
    }

    if (right < pq->size && pq->elements[right].priority < pq->elements[smallest].priority) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&pq->elements[i], &pq->elements[smallest]);
        heapify(pq, smallest);
    }
}

// Thêm phần tử vào priority queue
void enqueue(PriorityQueue *pq, int data, int priority) {
    if (pq->size == MAX_SIZE) {
        printf("Priority Queue is full!\n");
        return;
    }

    Element newElement = {data, priority};
    int i = pq->size;
    pq->elements[i] = newElement;
    pq->size++;

    // Heapify từ dưới lên
    while (i != 0 && pq->elements[(i - 1) / 2].priority > pq->elements[i].priority) {
        swap(&pq->elements[i], &pq->elements[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Xóa và trả về phần tử có mức độ ưu tiên cao nhất
Element dequeue(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("Priority Queue is empty!\n");
        Element empty = {-1, -1};
        return empty;
    }

    if (pq->size == 1) {
        pq->size--;
        return pq->elements[0];
    }

    Element root = pq->elements[0];
    pq->elements[0] = pq->elements[pq->size - 1];
    pq->size--;
    heapify(pq, 0);

    return root;
}

// Kiểm tra priority queue có rỗng không
int isEmpty(PriorityQueue *pq) {
    return pq->size == 0;
}

// In priority queue
void printQueue(PriorityQueue *pq) {
    if (isEmpty(pq)) {
        printf("Priority Queue is empty!\n");
        return;
    }

    printf("Priority Queue: ");
    for (int i = 0; i < pq->size; i++) {
        printf("(%d, %d) ", pq->elements[i].data, pq->elements[i].priority);
    }
    printf("\n");
}

// Hàm main để kiểm tra
int main() {
    PriorityQueue pq;
    init(&pq);

    // Thêm các phần tử vào priority queue
    enqueue(&pq, 10, 2);
    enqueue(&pq, 20, 1);
    enqueue(&pq, 30, 3);
    enqueue(&pq, 40, 0);

    // In priority queue
    printQueue(&pq);  // Kết quả: (40, 0) (20, 1) (30, 3) (10, 2)

    // Xóa phần tử có ưu tiên cao nhất
    Element e = dequeue(&pq);
    printf("Dequeued: (%d, %d)\n", e.data, e.priority);  // Kết quả: (40, 0)

    // In lại priority queue sau khi xóa
    printQueue(&pq);  // Kết quả: (20, 1) (10, 2) (30, 3)

    return 0;
}