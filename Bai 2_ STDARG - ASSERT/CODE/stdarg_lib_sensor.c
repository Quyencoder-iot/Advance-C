// Prog đọc dữ liệu từ nhiều cảm biến
#include <stdio.h>
#include <stdarg.h>

typedef enum {
    TEMPERATURE_SENSOR, // Nếu chưa gán giá trị thì mặc định TEMPRATURE_SENSOR = 0, PRESSURE_SENSOR = 1
    PRESSURE_SENSOR   
} SensorType;

void processSensorData(SensorType type, ...) { // Hàm đọc dữ liệu nhiều cảm biến, tham số 1 là kiểu cảm biến, ...: các tham số tiếp theo chưa xác định
    va_list args;
    va_start(args, type); // Bắt đầu tạo danh sách tham số
    switch (type) {       
        case TEMPERATURE_SENSOR: {
            int numArgs = va_arg(args, int); // biên numArgs là số lượng tham số tiếp theo truyền vào, ép kiểu int
            int sensorId = va_arg(args, int); //  id của sensor, ép kiểu int
            float temperature = va_arg(args, double); // giá trị nhiệt độ đọc được, kiểu ban đầu "float" được promote thành double để tăng độ chính xác.
            printf("Temperature Sensor ID: %d, Reading: %.2f degrees\n", sensorId, temperature); // 1st %d = sensorId, 2rd %.2f = temperature
            if (numArgs > 2) {  // Nếu số tham số tiếp theo >2, Xử lý thêm tham số nếu có
                char* additionalInfo = va_arg(args, char*);
                printf("Additional Info: %s\n", additionalInfo);
            }
            break;
        }
        case PRESSURE_SENSOR: {
            int numArgs = va_arg(args, int);
            int sensorId = va_arg(args, int);
            int pressure = va_arg(args, int);
            printf("Pressure Sensor ID: %d, Reading: %d Pa\n", sensorId, pressure);
            if (numArgs > 2) {
                // Xử lý thêm tham số nếu có
                char* unit = va_arg(args, char*);
                printf("Unit: %s\n", unit);
            }
            break;
        }
    }

    va_end(args); // kết thúc  list.
}

int main() {
    processSensorData(TEMPERATURE_SENSOR, 2, 1, 36.5, "Room Temperature");
    processSensorData(PRESSURE_SENSOR, 2, 2, 101325);
    return 0;
}


