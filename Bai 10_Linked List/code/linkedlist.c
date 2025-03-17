#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc Node cho danh sách liên kết
typedef struct Node {
    int data;           // Dữ liệu của nút
    struct Node* next;  // Con trỏ tới nút tiếp theo
} Node;

// Hàm chèn một nút vào đầu danh sách
// chèn vào đầu danh sách nên cần đổi địa chỉ node head => sang node mới nên phải dùng con trỏ cấp 2.
void push_front(Node** head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // Cấp phát bộ nhớ cho nút mới
    newNode->data = data;                        // Gán dữ liệu cho nút mới
    newNode->next = *head;                       // Nút mới trỏ tới nút đầu hiện tại
    *head = newNode;                             // Cập nhật đầu danh sách thành nút mới, Đổi địa chỉ node mới thành node head.
}

// Hàm chèn một nút vào cuối danh sách
// Do có trường hợp danh sách rỗng, *head =Null nên phải dùng con tro cấp 2 cập nhập địa chỉ mới cho node head.
void push_back(Node** head, int data) { // Tham số truyền vào là con trỏ cấp 2 => nó có thể thay đổi địa chỉ con trỏ câp 1.
    Node* newNode = (Node*)malloc(sizeof(Node)); // Cấp phát bộ nhớ cho nút mới
    newNode->data = data;                        // Gán dữ liệu cho nút mới
    newNode->next = NULL;                        // Nút mới là nút cuối, nên next là NULL
    
    if (*head == NULL) {                         // Kiêm tra Nếu danh sách rỗng
        *head = newNode;                         // Địa chỉ node head được gán bằng địa chỉ node mới. Nút mới trở thành nút đầu
        return;
    }
    
    Node* temp = *head;                          // Con trỏ tạm để duyệt danh sách tìm node cuối cùng
    while (temp->next != NULL) {                 // Duyệt tới nút cuối
        temp = temp->next;
    }
    temp->next = newNode;                        // Liên kết nút cuối với nút mới
}
// Hàm để thêm một nút mới vào giữa danh sách liên kết
void insertAfter(Node *prev_node, int new_data) { //tham số truyền vào là địa chỉ node trước, và data
    if (prev_node == NULL) {
        printf("Nút trước không được NULL\n");
        return;
    }

    Node* new_node = (Node*)malloc(sizeof(Node)); // cấp phát động bộ nhớ cho new_node
    new_node->data = new_data;
    new_node->next = prev_node->next; // Địa chỉ node mới trỏ đến gán băng đại chỉ đang lưu trong prev_node
    prev_node->next = new_node;
}

// Hàm xóa nút có giá trị cụ thể
// Nếu node đầu bị xóa phải cập nhập lại địa chỉ node đầu cho node kế tiếp.
void deleteNode(Node** head, int key) {
    Node* temp = *head;                          // Con trỏ tới nút hiện tại
    Node* prev = NULL;                           // Con trỏ tới nút trước đó
    
    // Nếu nút đầu là nút cần xóa
    if (temp != NULL && temp->data == key) {
        *head = temp->next;                      // Cập nhật đầu danh sách
        free(temp);                              // xóa node có data=key, Giải phóng bộ nhớ
        return;
    }
    
    // Tìm nút cần xóa
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) return;                    // Không tìm thấy nút
    
    prev->next = temp->next;                     // Bỏ qua nút cần xóa
    free(temp);                                  // Giải phóng bộ nhớ
}

// Hàm tìm kiếm nút có giá trị cụ thể
Node* search(Node* head, int key) {
    Node* current = head;                        // Con trỏ duyệt danh sách
    while (current != NULL) {
        if (current->data == key) return current;// Trả về nút nếu tìm thấy
        current = current->next;
    }
    return NULL;                                 // Trả về NULL nếu không tìm thấy
}

// Hàm hiển thị danh sách liên kết
void display(Node* head) {
    Node* temp = head;                           // Con trỏ duyệt danh sách
    while (temp != NULL) {
        printf("%d ", temp->data);               // In dữ liệu của nút
        temp = temp->next;
    }
    printf("\n");                                // Xuống dòng sau khi in xong
}

// Hàm xóa toàn bộ danh sách và giải phóng bộ nhớ
void deleteList(Node** head) {
    Node* current = *head;                       // tạo biến nút hiện tại để xóa, xóa xong gán biến này cho node kế tiếp và xóa tiếp
    Node* next;                                  // Con trỏ tới nút tiếp theo
    while (current != NULL) {                     
        next = current->next;                    // Lưu nút tiếp theo
        free(current);                           // Giải phóng nút hiện tại
        current = next;                          // Chuyển sang nút tiếp theo
    }
    *head = NULL;                                // Đặt đầu danh sách về NULL
}

// Hàm chính để kiểm tra các thao tác trên danh sách liên kết
int main() {
    Node* head = NULL;                           // Khởi tạo danh sách rỗng
    
    // Chèn các phần tử
    push_front(&head, 1);                 // Chèn 1 vào đầu
    push_front(&head, 2);                 // Chèn 2 vào đầu
    push_back(&head, 3);                       // Chèn 3 vào cuối
    
    printf("Danh sach ban dau: ");
    display(head);                               // Hiển thị: 2 1 3
    
    deleteNode(&head, 1);                        // Xóa nút có giá trị 1
    printf("Danh sach sau khi xoa 1: ");
    display(head);                               // Hiển thị: 2 3
    
    Node* found = search(head, 2);               // Tìm nút có giá trị 2
    if (found != NULL) {
        printf("Tim thay: %d\n", found->data);   // In kết quả tìm kiếm
    }
    
    deleteList(&head);                           // Xóa toàn bộ danh sách
    
    return 0;
}