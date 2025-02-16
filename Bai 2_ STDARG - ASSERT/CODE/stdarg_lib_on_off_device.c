// Pro tạo các lệnh điều khiển (Turn on/off, set level, send message) cho nhiều thiết bị theo ID từng thiết bị.
#include <stdio.h>
#include <stdarg.h>

typedef enum {  // kiểu enum = enumeration là 1 tập hợp hằng số có tên gọi, đại diện cho 1 nhóm giá trị. thường dùng vs hàm switch case
    TURN_ON,
    TURN_OFF,
    SET_LEVEL,
    SEND_MESSAGE
} CommandType; // Tao struct lenh dieu khien (bật, tắt, cài mức, gửi thông điệp)
void sendCommand(CommandType command, ...) { // tham số 1: là command, ...: tham số tiếp theo chưa xác định.
    va_list args;   // tạo list tham số args.
    va_start(args, command); // Bắt đầu tạo list tham số, tham số 1 gán = command.

    switch (command) {  
        case TURN_ON:
        case TURN_OFF: { 
            int deviceID = va_arg(args, int); // tham số id của thiết bị, kép kiểu int
            printf("Command: %s Device ID: %d\n", command == TURN_ON ? "Turn On" : "Turn Off", deviceID);
            break;
        /*
        %s = command == TURN_ON ? "Turn On" : "Turn Off" : là biểu thức có điều kiện
        %d = deviceID
        
        */
        }
        case SET_LEVEL: {
            int deviceID = va_arg(args, int); // id máy, ép kiểu int
            int level = va_arg(args, int); //  level, ép kiểu int
            printf("Set Level of Device ID %d to %d\n", deviceID, level);
            break;
        }
        case SEND_MESSAGE: {
            char* message = va_arg(args, char*); 
            printf("Send Message: %s\n", message); 
            break;
        }
    }

    va_end(args);
}

int main() {
    sendCommand(TURN_ON, 1);
    sendCommand(TURN_OFF, 2);
    sendCommand(SET_LEVEL, 3, 75);
    sendCommand(SEND_MESSAGE, "Hello World");
    return 0;
}
