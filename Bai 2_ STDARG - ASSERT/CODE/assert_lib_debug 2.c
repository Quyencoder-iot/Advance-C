#include <assert.h>
#include <stdint.h>

#define ASSERT_SIZE(type, size) assert(sizeof(type) == (size))

void checkTypeSizes() {
    ASSERT_SIZE(int, 4);
// Kiểm tra các kích thước kiểu dữ liệu khác
}
