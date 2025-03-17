#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc một nút trong danh sách liên kết đơn
struct Node {
    int data;
    struct Node *next;
};

// Hàm để in danh sách liên kết
void printList(struct Node *node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// Hàm để thêm một nút mới vào đầu danh sách liên kết
void insertAtBeginning(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

// Hàm để thêm một nút mới vào cuối danh sách liên kết
void insertAtEnd(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node *last = *head_ref;

    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new_node;
}

// Hàm để thêm một nút mới vào giữa danh sách liên kết
void insertAfter(struct Node *prev_node, int new_data) {
    if (prev_node == NULL) {
        printf("Nút trước không được NULL\n");
        return;
    }

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}

// Chương trình chính để kiểm tra các hàm thêm
int main() {
    struct Node* head = NULL;

    // Thêm các nút vào cuối danh sách
    insertAtEnd(&head, 1);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 3);

    printf("Danh sách sau khi thêm vào cuối: ");
    printList(head);

    // Thêm một nút vào đầu danh sách
    insertAtBeginning(&head, 0);

    printf("Danh sách sau khi thêm vào đầu: ");
    printList(head);

    // Thêm một nút vào giữa danh sách (sau nút thứ hai)
    insertAfter(head->next, 1);

    printf("Danh sách sau khi thêm vào giữa: ");
    printList(head);

    return 0;
}
