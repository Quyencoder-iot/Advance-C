/**
 *@brief: Chương trinh triển khai cấu trúc dữ liệu JSON bằng ngôn ngữ C, JSON là 1 cấu trúc dữ liệu trong javacript
 Nó có thể chứa tất cả các kiểu dữ liệu. Do không sẵn có thư viên trong C nên phải xây dựng chương trình thao tác đọc, ghi, hiển thị loai dữ liệu này
 JSON có 2 kiểu chính là 
 *Object (gồm các cặp key:value khai báo trong dấu {}) 
 *Array (có thế chứa object, mảng, biến, kiểu dữ liệu bất kỳ của C được khai báo trong dấu [])
 xây dựng các kiểu dữ liệu JSON gồm (NULL, BOOLEAN, NUMBER, STRING,ARRAY, OBJECT) dùng typedef enum, struct, union
 create hàm để phân tích kiểu dữ liêu JSON này và cập nhập giá trị vào biến con trỏ
 *@param: Các hàm phân tích truyền vào 1 tham số là con tro cấp 2 **json  (chính là vị trí kí tự), dùng con tro cấp hai để có thê thay đổi địa chỉ đầu con trỏ (nếu cần) khi gặp khoảng trắng
 *@return: trả về con tro kiêu JsonValue. hàm trả về con trỏ nghĩa là bạn phải cập nhập giá trị cho các thành viên của con tro.
 *ví dụ: 
 - return con tro kiểu mảng => cập nhập giá trị cho các phần tử trong mảng, 
 - return con tro kiểu struct, union => cập nhập giá trị cho các thành viên, phần tử trong struct và union đó
 *@note : 
 biện pháp phân tích các kiểu dự liệu JSON là ta biến tất cả thành chuỗi trong C, và phân tích từng ký tự để bóc tách từng kiểu dữ liệu. 
 *Việc phân tích qua 2 bước :
    1. Phân tích thô => khi duyệt đến ký tự mà bạn nghi ngờ nó là bắt đầu kiểu dữ liệu nào đó
    như ký tự n = null, t,f: true, false=> boolean, \" : bắt đầu string, [: bắt đầu array, {: bắt đầu object
    return : trả về các hàm phân tích chuyển sâu tương ứng.
    2. Lập tức trả về 1 hàm phân tích chuyên sâu parse_null, parse_boolean, parse_string, parse_array, parse_object
    hàm phân tích chuyển sâu giá trị trả về (return) là con trỏ, bạn có nhiệm vụ gán giá trị cho các thành viên, phần tử trong con trỏ đó
*/
/**
*@brief:include thư viện cần thiết
* stdio.h: Dùng cho input/output (ví dụ: printf).
* string.h: Cung cấp các hàm thao tác chuỗi như strncmp, strncpy.
* stdlib.h: Cung cấp các hàm như malloc, realloc, free, và strtod để cấp bộ nhớ, chuyển đổi chuỗi sang số...
* stddef.h: Định nghĩa size_t.
* ctype.h: Cung cấp isspace để kiểm tra ký tự trắng.
* stdbool.h: Định nghĩa kiểu bool (true, false).
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>
/**
*@brief: dùng enum Liệt kê các kiểu dữ liệu JSON (null, boolean,number, string, array, object)
Định nghĩa chúng là JsonType.
*/
typedef enum {
    JSON_NULL,
    JSON_BOOLEAN,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JsonType;
/**
*@brief: Tạo 1 struct JsonValue chứa các thành viên
*type: thanh viên có kiểu JsonType: mục đích để ánh xạ định nghĩa cho các kiểu dữ liệu sau này trong các hàm
*union: khai báo ban đầu cho cấu trúc gồm nhiều kiểu dữ liệu (boolean, number, string, array, object)
* cụ thể hóa các các kiểu dữ liệu sẽ được thực hiện trong các hàm parse_null, parse_boolean, parse_string, parse_array, parse_objec
* Đối với struct object, do mỗi object gồm nhiều cặp key-value, mà mỗi key là 1 chuỗi string
* array và object được khai báo đệ quy => biến values cũng đầy đủ thành viên của Jsonvalue.
* Trong C, một chuỗi ký tự (string) được biểu diễn bằng một con trỏ tới ký tự đầu tiên của chuỗi
* Do trong object có nhiều chuỗi key (string) nên cần 1 mảng con trỏ để quản lý 
*Trong C, một mảng của các con trỏ được khai báo bằng cú pháp char *array[] hoặc char **array =[*key1,*key2,...] => dùng con trỏ cấp 2 dễ dàng nhất
*/
typedef struct JsonValue {
    JsonType type; // Dùng để ánh xạ, gán các kiểu dữ liệu trong union đến phần tên liệt kê trong JsonType trong các hàm sau này
    union { 
        int boolean;  // mục đích để ánh xạ kiểu Json_boolean tới kiểu boolean trong C
        double number; // mục đích để ánh xạ kiểu Json_number tới kiểu nubmer trong C
        char *string; // mục đích để ánh xạ kiểu Json_string tới kiểu string trong C
        struct {
            struct JsonValue *values; // array là một struct đệ quy JsonValue do cung tập hợp kiểu dữ liệu
            size_t count; // đếm số phần tử của mảng
        } array; // Khai báo array là 1 struct đệ quy kiểu JsonValue, có biến đếm số thành viên count
        struct {
            char **keys; // Do mỗi key là một chuỗi string, cần 1 con trỏ để quản lý. object chứa nhiều keys nên cần một mảng con trỏ => phải sử dụng con tro cấp 2
            struct JsonValue *values; // khai báo object là một struct đệ quy JsonValue do cung tập hợp kiểu dữ liệu
            size_t count; // Đếm số cặp keys-values
        } object;   //khai báo object (gồm cặp key-value, biến count đếm số cặp key-value,  value là 1 struct đệ quy kiểu JsonValue.
    } value;
} JsonValue;

/**
*@brief: parse_json Hàm phân tích thô chuỗi json, Tên hàm để trên đầu nhưng code cụ thể của nó để ở cuối chương trình.
* Câu hỏi: tại sao tên hàm được đặt đầu chương trình, code lại có thể ở cuối chương trình 
*=> Trả lời : do giá trị mảng array và object được khai báo đệ quy (do các phần tử có kiểu dữ liệu bất kỳ : string, object,number...)
nên mỗi phần tử phải được phân tích lại từ đầu như một chuỗi json khác => cần gọi lại hàm parse_json() cho mỗi phần tử.
*Trong C, để phân tích chuỗi json phải chuyển nó thành chuỗi kỹ tự, sau đó phân tích từng ký tự để xem nó thuộc kiểu dữ liệu này
* Hàm này thực hiện nhận diện ký tự ở mức thô. nếu phát hiện ký tự là các ký tự sau nó sẽ chuyển đến hàm phân tích chuyên sâu hơn
*ý tưởng phân tích: ký tự n = null, t,f: true, false=> boolean, \" : bắt đầu string, [: bắt đầu array, {: bắt đầu object
*mỗi ký tự trên sẽ trả về 1 hàm phân tích chuyên sâu parse_null, parse_boolean, parse_string, parse_array, parse_object
*/
JsonValue *parse_json(const char **json); 

/**
*@brief: free_json_value có tham số truyền vào là con trỏ cấp một kiểu JsonValue
*/
void free_json_value(JsonValue *json_value);

/**
*@brief: skip_whitespace để bỏ khoảng trắng ở đầu mỗi chuỗi key,bằng cách đổi địa chỉ trỏ đến ký tự đầu chuỗi.
*=>do mỗi chuỗi đại diện bởi 1 con trỏ trỏ đến ký tự đầu chuỗi nên đầu chuỗi có khoảng trắng thì phải thay đổi địa chỉ trỏ đến ký tự tiếp theo
để thay đổi địa chỉ con trỏ buộc phải dùng con trỏ cấp 2. nếu dùng con trỏ cấp 1 thì địa chỉ sẽ không thay đổi khi thoát khỏi hàm.
* Hàm isspace() là một hàm có sẵn trong thư viện chuẩn C (ctype.h), 
dùng để kiểm tra xem một ký tự có phải là ký tự khoảng trắng hay không (ví dụ: ' ', '\t', '\n', '\r', v.v.)
*json : giải tham chiếu 2 lần để lấy giá trị lưu trong con trỏ *json
* const char: khai báo "const" để hàm chỉ đọc chuỗi mà không vô tình ghi thay đổi được chuỗi ký tự.
* static : giúp hàm skip_whiespace là duy nhất, không thể khai báo 1 hàm trùng tên trong folder chương trình.
*/
static void skip_whitespace(const char **json) { // Dùng static cho phép hàm skip_whitespace chỉ được dùng trong file này.
    while(isspace(**json))  {
    (*json)++; // chuyển đến địa chỉ của chuỗi key (string) tiếp theo
    }
}
/**
*@brief: Hàm kiểm tra ký tự Null, cập nhập giá trị cho con trỏ kiểu JsonValue
*@param: truyền vào 1 tham số là con trỏ cấp 2, do phải có hàm kiểm tra khoảng trắng skip_whitespace
*@return: trả về con trỏ kiểu JsonValue. trong đó giá trị thành viên thay đổi là : type = JSON_NULL,
*@note:
-strncmp là hàm trong thử viện string.h, truyền vào 3 tham số (1. con trỏ ký tự, 2.string cần so sánh, 3. số ký tự so sánh)
- hàm trả về 0 nếu chuỗi giống nhau, dương hoặc âm nếu chuỗi khác nhau.
- chú ý giá trị trả về bắt buộc là con trỏ nếu nó trả về 1 mảng, chuỗi, object nhiều phần tử.
*/
JsonValue *parse_null(const char **json) {
    skip_whitespace(json); // Bỏ qua qua khoảng trắng, thay đổi địa chỉ con trỏ trỏ đến ký tự đầu chuỗi.
    if (strncmp(*json, "null", 4) == 0) { // So sánh 4 ký tự đúng = null
        JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue)); // Cấp phát bộ nhớ động cho con trỏ value.
        value->type = JSON_NULL; // gán kiểu dữ liệu JSON_NULL
        *json += 4; // bỏ qua 4 ký tự, tiếp tục duyệt ký tự tiếp theo.
        return value; // giá trị trả về là địa chỉ con trỏ value hay vùng nhớ chứa chuỗi là kiểu JSON_NULL.
    }
    return NULL;
}
/**
*@brief:Parse_boolean phân tích xem chuỗi có phải kiểu boolean không và cập nhập giá trị cho con trỏ kiểu JsonValue
*@param: truyền vào 1 tham số là con trỏ cấp 2, do phải có hàm kiểm tra khoảng 
*@param:truyền vào 1 tham số là con tro cấp 2, do có hàm kiểm tra khoảng trắng và đổi địa chỉ con tro nếu cần.
*@return: tra về con trỏ kiểu JsonValue, thành viên type = JSON_BOOLEAN, boolean = true or false, nếu chuỗi không phải boolean trả về null
*@note:cách phân tích giống parse_null ở trên
*/
JsonValue *parse_boolean(const char **json) {
    skip_whitespace(json);
    JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
    if (strncmp(*json, "true", 4) == 0) {
        value->type = JSON_BOOLEAN; // gán enum JSON_BOOLEAN cho type
        value->value.boolean = true; // boolean = tre
        *json += 4;
    } else if (strncmp(*json, "false", 5) == 0) {
        value->type = JSON_BOOLEAN;
        value->value.boolean = false; 
        *json += 5; // bỏ qua 5 ký tự này, chuyển đến duyệt ký tự tiếp theo
    } else {
        free(value); // nếu if sai giải phóng bộ nhớ động cấp cho value.
        return NULL; // trả về null nếu if sai.
    }
    return value;
}
/**
*@brief:Parse_number chuyển chuỗi ký tự số đó thành number cập nhập giá trị cho con trỏ kiểu JsonValue
*@param: truyền vào 1 tham số là con trỏ cấp 2, do phải có hàm kiểm tra khoảng 
*@param:truyền vào 1 tham số là con tro cấp 2, do có hàm kiểm tra khoảng trắng và đổi địa chỉ con tro nếu cần.
*@return: tra về con trỏ kiểu JsonValue, gán thành viên type = JSON_NUMBER, boolean = true or false, nếu chuỗi không phải boolean trả về null
*@note:
-trong hàm pt thô parse_json(), sử dụng hàm isdigit() (thư viện ctype.h) nhận diện chuỗi số chính xác. nên ông việc của parse_number chỉ 
- công 
-double strtod(const char *str, char **endptr)
-hàm truyền vào 2 tham số (1.con trỏ str trỏ đến đầu chuỗi số, 2.endptr lưu vị trí chuỗi ký tự ngay sau khi chuyển đổi để các nhận chuỗi đã được đọc chưa  )
-trả về kiểu số double.
*/
JsonValue *parse_number(const char **json) {
    skip_whitespace(json);
    char *end;
    double num = strtod(*json, &end); // strtod: chuyển chuỗi ký tự thành số kiểu double
    if (end != *json) { // nếu vị trí end khác vị trí đầu (so sánh địa chỉ) thì thực hiện cấp bộ nhớ động, gán kiểu dữ liệu, và gán giá trị só 
        JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue)); // cấp bộ nhớ động cho con trỏ value
        value->type = JSON_NUMBER; // gán kiểu dữ liệu type
        value->value.number = num; //cập nhập số numb vào biến number
        *json = end;// đổi vị địa chỉ đầu chuỗi json đến vị tri end
        return value; // return con trỏ value đã được gán giá trị cho các thành viên
    }
    return NULL;
}
/**
*@brief:Parse_string phân tích xem chuỗi có phải kiểu string không cập nhập giá trị cho con trỏ kiểu JsonValue
*@param: truyền vào 1 tham số là con trỏ cấp 2, do phải có hàm kiểm tra khoảng 
*@param:truyền vào 1 tham số là con tro cấp 2, do có hàm kiểm tra khoảng trắng và thay đổi địa chỉ đầu của con tro nếu cần.
*@return: trả về con trỏ kiểu JsonValue, gán giá trị cho thành viên mà con trỏ trỏ đến type = JSON_STRING, string = str
*@note: 
*Đặc điểm chuỗi string trong C/C++
- các chuỗi con trong chuỗi json được đặt trong \"...\"
- môt chuỗi string luôn kết thúc bằng ký tự null (\0)
*với con trỏ cấp 2 json:
**json = saved value of pointer, *json = address con trỏ cấp 1, json = address con trỏ cấp 2.
*ham strncpy :sao chép một số lượng ký tự nhất định từ chuỗi nguồn (source) sang chuỗi đích (destination)
char *strncpy(char *destination, const char *source, size_t num)
hàm cần truyền vào 3 tham số (1.địa chỉ đích, 2.địa chỉ nguồn string, 3.số ký tự tối đa copy sang)
*/
JsonValue *parse_string(const char **json) {
    skip_whitespace(json);

    if (**json == '\"') {
        (*json)++; // trỏ đến ký tự kế tiếp
        const char *start = *json; // start lưu địa chỉ đầu của chuỗi
        while (**json != '\"' && **json != '\0') { // chờ gặp ký tự cuối chuỗi (\") hoặc ký tự null (\0) thì thoát vòng lặp vô tận
            (*json)++;// duyệt tới ký tự tiếp theo
        }
        if (**json == '\"') { // nếu duyệt đến cuối chuỗi thực hiện xác định kích thước chuỗi, gán chuỗi vào 1 con trỏ str, gán vị trí cuối chuỗi =null
            size_t length = *json - start; // kích thước chuỗi = địa chỉ cuối - đầu
            char *str = (char *) malloc((length + 1) * sizeof(char)); // cấp phát động đủ bộ nhớ cho con tro str, tránh lãng phí bộ nhớ
            strncpy(str, start, length); // copy chuỗi ký tự sang địa chỉ con tro str từ địa chỉ start
            str[length] = '\0';

            JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
            value->type = JSON_STRING; // gán giá trị cho tham số type của con tro value
            value->value.string = str; // gán giá trị cho tham số string trong con tro value
            (*json)++;
            return value; // trả lại con tro value sau khi đã được gán giá trị cho từng tham số.
        }
    }
    return NULL;
}
/**
*@brief:Parse_array phân tích xem chuỗi có phải kiểu array không
*@param:truyền vào 1 tham số là con tro cấp 2, do có hàm kiểm tra khoảng trắng và thay đổi địa chỉ đầu con tro nếu cần.
*@return: tra về con trỏ kiểu JsonValue, update giá trị cho các thành viên mà con trỏ trỏ đến: type, array.count, array.value
*@note:
- Do phần tử của của mảng nó có thể là bất cứ kiểu dữ liệu nào (number,string, boolean, object,...)
- giá trị phần tử của mảng cũng được khai báo kiểu đệ quy struct JsonValue *values 
- Nên thủ thuật ở đây là từng phần tử của mảng phải được phân tích lại từ đầu => gọi lại hàm phân tích thô parse_json.
*/
JsonValue *parse_array(const char **json) {
    skip_whitespace(json);
    if (**json == '[') {
        (*json)++;// tăng địa chỉ 1 đơn vị để duyệt ký tự tiếp theo
        skip_whitespace(json);// hàm bỏ qua khoảng trắng đầu chuỗi trỏ đến ký tự thật
        JsonValue *array_value = (JsonValue *)malloc(sizeof(JsonValue)); // cấp phát động đủ bộ nhớ cần thiết lần đầu cho con tro array_value , để tiện kiệm memory lưu trữ
        array_value->type = JSON_ARRAY;
        array_value->value.array.count = 0; // khởi tạo count =0
        array_value->value.array.values = NULL;//  khởi tạo con trỏ values = NULL (tức là không trỏ đến địa chỉ nào)

        /*
        double arr[2] = {};
        arr[0] = 30;
        arr[1] = 70;
        */

        while (**json != ']' && **json != '\0') { // Đợi đến khi gặp ký tự ']' hoặc null thoát vòng lặp, khi điều kiện chưa đáp ứng thực hiện công việc dưới đây
            JsonValue *element = parse_json(json); // Gọi lại hàm phân tích thô cho từng phần tử mảng, nếu phần tử mảng thuộc kiểu nào nó nhảy vào hàm parse_number, parse_string, parse_object,parse_boolean tương ứng. và giá trị được cập nhập vào con trỏ element.
            if (element) { // nếu phần tử hợp lệ (element khác null=> điều kiện = true) 
                array_value->value.array.count++; // tăng count để ghi nhận số phần tử mảng
                array_value->value.array.values = (JsonValue *)realloc(array_value->value.array.values, array_value->value.array.count * sizeof(JsonValue));// tăng kích thước bộ nhớ động cho array_value cho phần tử value.array.values sắp được lưu vào mảng
                array_value->value.array.values[array_value->value.array.count - 1] = *element;
                free(element);//Giải phóng bộ nhớ tạm thời được cấp cho element sau khi thêm vào mảng
            } else {
                break;
            }
            skip_whitespace(json);
            if (**json == ',') { // nếu gặp dấu , chuyển sang phần tử tiếp theo
                (*json)++; // tăng địa chỉ lên 1 để duyệt ký tự tiếp theo, do lúc này nó vẫn chưa thoát khỏi vòng lặp while được nên quay lại từ code từ element
            }
        }
        if (**json == ']') {
            (*json)++;
            return array_value;
        } else {
            free_json_value(array_value);// giải phóng bộ nhớ tạm cấp cho con tro array_value
            return NULL;
        }
    }
    return NULL;
}
/**
*@brief:Parse_object phân tích xem chuỗi có phải kiểu object không và lưu giá trị vào object
*@param:truyền vào 1 tham số là con tro cấp 2, do có hàm kiểm tra khoảng trắng và thay đổi địa chỉ đầu con tro nếu cần.
*@return: tra về con trỏ kiểu JsonValue, update giá trị cho các thành viên mà con trỏ trỏ đến: key, values, count
*@note:
*Cặp key-value có đặc điểm:
- key kiểu string nên gọi hàm phân tích parse_string để cập nhập giá trị cho nó
- value có kiểu dữ liệu bất kỳ (number,string, boolean, object,...) và được khai báo đệ quy "struct JsonValue values"
nên thủ thuật ở đây : value cần được phân tích lại từ đầu như 1 chuỗi json con => bằng gọi hàm parse_json(): hàm này phân tích thô và chuyển đến hàm phân tích chuyển sâu để cập nhập giá tri
giá trị cập nhập có thể lưu vào biến con trỏ tạm.
*/
JsonValue *parse_object(const char **json) {
    skip_whitespace(json);
    if (**json == '{') { // nếu gặp dấu mở object
        (*json)++;
        skip_whitespace(json);

        JsonValue *object_value = (JsonValue *)malloc(sizeof(JsonValue)); // cấp động đủ bộ nhớ cho con trỏ object_value
        object_value->type = JSON_OBJECT; // update kiêu dữ liệu cho type
        object_value->value.object.count = 0; // khởi tạo count =0
        object_value->value.object.keys = NULL; // khởi tạo con trỏ cấp 2 keys = null
        object_value->value.object.values = NULL; // khởi tạo con trỏ cấp 1 values =null

        while (**json != '}' && **json != '\0') {// vòng lặp vô tận khi chưa gặp ký tự đóng object '}' hoặc ký tự null (chỉ gặp null khi nó là kết thúc của chuỗi string)
            JsonValue *key = parse_string(json); // do key là string nên gọi hàm phân tích string để cập nhập giá trị vào con trỏ key
            if (key) { // nếu key hợp lệ (tức khác null => điều kiện hàm = true)
                skip_whitespace(json);
                if (**json == ':') { // găp dấu phân cách ":" chuyển sang phân tích values 
                    (*json)++;
                    JsonValue *value = parse_json(json);// gọi hàm phân tích parse_json để phân tích value như 1 chuỗi json và cập nhập giá trị vào biên con tro tạm value
                    if (value) {
                        object_value->value.object.count++; // tăng count để ghi nhận thêm cặp key-value
                        object_value->value.object.keys = (char **)realloc(object_value->value.object.keys, object_value->value.object.count * sizeof(char *));// cấp phát thêm bộ nhớ cho thành viên keys của con trỏ.
                        object_value->value.object.keys[object_value->value.object.count - 1] = key->value.string; // cập nhập giá trị từ con trỏ tạm key vào con trỏ keys

                        object_value->value.object.values = (JsonValue *)realloc(object_value->value.object.values, object_value->value.object.count * sizeof(JsonValue));
                        object_value->value.object.values[object_value->value.object.count - 1] = *value; // câp nhập giá trị cho thành viên values của con trỏ trả về
                        free(value);// giải phóng bộ nhớ tạm cấp cho value
                    } else {
                        free_json_value(key); // giải phóng bộ nhớ tạm cấp cho key
                        break;
                    }
                } else {
                    free_json_value(key);
                    break;
                }
            } else {
                break;
            }
            skip_whitespace(json);
            if (**json == ',') { // gặp ký tự , thì chuyển sang cặp key-value khác. do lúc này chưa thể thoát khỏi while nên chương trình quay lại bước 1 chỗ phân tích key
                (*json)++;
            }
        }
        if (**json == '}') {
            (*json)++;
            return object_value;
        } else {
            free_json_value(object_value);
            return NULL;
        }
    }
    return NULL;
}

/////////////

/////////////

/**
*@brief:parse_json Hàm phân tích chuỗi json , tham số truyền vào là con trỏ cấp 2 để có thể thay đổi địa chỉ trỏ đến, thay đổi này áp dụng cả phạm vi ngoài hàm
* Đây là hàm kiểm tra thô ký tự đầu tiên => tức là nếu nghi ngờ là kiểu dữ liệu nào thì trả về hàm phân tích parse tương ứng để phân tích kỹ hơn.
* Tại sao phải phân tích ??? => do chuỗi json chứa nhiều kiểu dữ liệu hỗn tạp khác nhau. Để hiểu được chuỗi, trong C chuyển nó thành chuỗi ký tự, sau đó phân tích từng ký tự 1 để biết được đó là object, mảng, number hay string
*ý tưởng phân tích: ký tự n = null, t,f: true, false=> boolean, \" : bắt đầu string, [: bắt đầu array, {: bắt đầu object
*/
JsonValue *parse_json(const char **json) { 
    while (isspace(**json)) {
        (*json)++; // trỏ đến địa chỉ tiếp theo bỏ qua khoảng trắng
    }

    switch (**json) { // **json : giải tham chiếu 2 lần trả lại ký tự lưu trong địa chỉ json trỏ đến.
        case 'n':
            return parse_null(json);
        case 't':
        case 'f':
            return parse_boolean(json); // ký tự t,f = true, false : trả lại kiểu boolean.
        case '\"':
            return parse_string(json);
        case '[':
            return parse_array(json);
        case '{':
            return parse_object(json); // gặp ký tự "{" : Trả về hàm phân tích object.
        default:
        //isdigit: hàm trong thư viện ctype.h : kiểm tra ký tự có phải số không
        // || : toán tử hoặc, ký tự **json = '-': bắt đầu bằng dấu trừ thì mặc định đó bắt đầu số âm trả về hàm kiểm tra số parse_number
            if (isdigit(**json) || **json == '-') { 
                return parse_number(json);
            } else {
                // Lỗi phân tích cú pháp
                return NULL;
            }
    }
}
/**
*@brief:free_json_value hàm giải phóng bộ nhớ đã cấp phát động cho một biến kiểu json_value
*@param: truyền vào con tro json_value trỏ đến vùng nhớ được cấp phát động
*@return: void không yêu cầu giá trị trả về hoặc có thể ép kiểu bất kỳ cho giá trị trả về
*@note: 
*Case JSON_ARRAY chứa 
- count : số phần tử trong mảng
- values: Con trỏ trỏ đến mảng JsonValue(mỗi phần tử là 1 giá trị JSON)
=> Để giải phóng bộ nhớ cần thực hiện giải phóng bộ nhớ động của từng phần tử, 
sau đó giải phóng bộ nhớ động cấp phát cho con trỏ
*Case Object
- count: Số lượng cặp key-value trong đối tượng.
- keys: Một con trỏ cấp 2 lưu trữ các địa chỉ của các con trỏ câp 1 trỏ đến các chuỗi keys. [*key1,*key2,...]
- values: Một con trỏ tới mảng các JsonValue, lưu trữ các giá trị tương ứng.
=>Do có 2 con tro keys và values nên việc giải phóng bộ nhớ cần 2 bước
Giải phóng bộ nhớ động từng phần tử mảng 2 con trỏ trỏ đến. rồi mới giải phóng bộ nhớ cho chính con trỏ đó.
nhớ giá trị truyền vào là địa chỉ
phải giải phóng bộ nhớ do khi cấp phát động cho biến, phần tử bằng malloc, realloc thì bộ nhớ sẽ được lưu trữ suốt chương trình.
*/
void free_json_value(JsonValue *json_value) {
    if (json_value == NULL) {
        return;
    }
    
    switch (json_value->type) { //type gồm 6 kiểu dữ liêu JsonValue định nghĩa trong typedef enum ở trên
        case JSON_STRING:
            free(json_value->value.string);
            break;
        case JSON_ARRAY:
            for (size_t i = 0; i < json_value->value.array.count; i++) { // duyệt từng phẩn tử của mảng để giải phóng bộ nhớ, count là phân tử của array đếm số phần tử của array
                free_json_value(&json_value->value.array.values[i]); // Gọi đệ quy để giải phóng bộ nhớ cho từng phần tử
            }
            free(json_value->value.array.values); // giải phóng bộ nhớ động con trỏ
            break;
        case JSON_OBJECT:
            for (size_t i = 0; i < json_value->value.object.count; i++) { //duyệt từng phần tử
                free(json_value->value.object.keys[i]); // key[i] địa chỉ chuỗi key i. giải phóng bộ nhớ từng phần tử keys. 
                free_json_value(&json_value->value.object.values[i]); // Gọi đệ quy để giải phóng bộ nhớ cho từng phần tử
            }
            free(json_value->value.object.keys); // keys : địa chỉ con trỏ cấp 2. hàm giải phóng bộ nhớ cho con trỏ này
            free(json_value->value.object.values); // values: địa chỉ con trỏ cấp 1. hàm giải phóng bộ nhớ cho con trỏ này
            break;
        default:
            break;
    }
}
/**
*@brief:hàm display hiển thị chuỗi json
*@param: truyền vào 1 tham số là con trỏ cấp 1 json (địa chỉ của chuỗi json)
*@return: trả lại kiểu void (trống) - có nghĩa không yêu cầu trả về kiểu dữ liêu
*@note:
* do hàm printf() chỉ hỗ trợ in các kiểu string,number, boolean. 
Nên nếu là Object hay Array thì ta lại phải bóc tách ra thêm lần nữa
mỗi cặp keys-values thì 
- keys là kiểu string in dễ dàng bằng printf(), 
- values là con trỏ cấp 1, lưu trưc tiếp các phân tử, mỗi phần tử có kiểu dữ liêu number, string, boolean.
=> cần duyệt xem mỗi phần tử values[i] xem mỗi phần tử kiểu gì để in ra.

*/
void display(JsonValue* json_value){

    if (json_value != NULL && json_value->type == JSON_OBJECT) {
        // Truy cập giá trị của các trường trong đối tượng JSON
        size_t num_fields = json_value->value.object.count;
        size_t num_fields2 = json_value->value.object.values->value.object.count; // giá trị values cũng là 1 kiểu object nên nó cũng chưa count và value 
        for (size_t i = 0; i < num_fields; ++i) { // duyệt từng cặp key-value của object
        // Lần lượt gán giá trị của keys, values, type của object vào các biến con tro tạm key, value, type.
            char* key = json_value->value.object.keys[i]; // keys là con tro cấp 2 => keys[]: con trỏ cấp 1 được lưu tạm vào con trỏ key.
            JsonValue* value = &json_value->value.object.values[i]; // values là con trỏ cấp 1, values[] là giá trị. lưu vào con tro value nên value = &values[]
            JsonType type = (int)(json_value->value.object.values[i].type); // lưu kiểu của values[i] vào con trỏ type.

            // duyệt từng kiểu dữ liệu của values[i] để gọi hàm printf tương ứng.
            if(type == JSON_STRING){
                printf("%s: %s\n", key, value->value.string);
            }

            if(type == JSON_NUMBER){
                printf("%s: %f\n", key, value->value.number);
            }

            if(type == JSON_BOOLEAN){
                printf("%s: %s\n", key, value->value.boolean ? "True":"False");
            }

            if(type == JSON_OBJECT){ // nếu là kiểu OBJECT thì gọi đệ quy hàm display(value) để bóc tách thêm lần nươc.
                printf("%s: \n", key);
                display(value); // gọi đệ quy value để bóc tách thêm lần nữa.
            }

            if(type == JSON_ARRAY){
                printf("%s: ", key);
                for (int i = 0; i < value->value.array.count; i++)
                {
                   display(value->value.array.values + i); // do values là object nên gọi đệ quy display() thêm 1 lần.
                } 
                printf("\n");
            }

  
        }

     
    }
    else 
    {
            if(json_value->type == JSON_STRING){
                printf("%s ", json_value->value.string);
            }

            if(json_value->type == JSON_NUMBER){
                printf("%f ", json_value->value.number);
            }

            if(json_value->type == JSON_BOOLEAN){
                printf("%s ", json_value->value.boolean ? "True":"False");
            }

            if(json_value->type == JSON_OBJECT){
                printf("%s: \n", json_value->value.object.keys);
                display(json_value->value.object.values);
                           
            }
    }

}


int main(int argc, char const *argv[])
{
     // Chuỗi JSON đầu vào, chuỗi con trong chuỗi json phải đặt trong dấu như sau : \" sub_string \" thì C mới hiểu được
    const char* json_str = "{"
                        "\"1001\":{"
                          "\"SoPhong\":3,"
                          "\"NguoiThue\":{"
                            "\"Ten\":\"Nguyen Van A\","
                            "\"CCCD\":\"1920517781\","
                            "\"Tuoi\":26,"
                            "\"ThuongTru\":{"
                              "\"Duong\":\"73 Ba Huyen Thanh Quan\","
                              "\"Phuong_Xa\":\"Phuong 6\","
                              "\"Tinh_TP\":\"Ho Chi Minh\""
                            "}"
                          "},"
                          "\"SoNguoiO\":{"
                            "\"1\":\"Nguyen Van A\","
                            "\"2\":\"Nguyen Van B\","
                            "\"3\":\"Nguyen Van C\""
                          "},"
                          "\"TienDien\": [24, 56, 98],"
                          "\"TienNuoc\":30.000"
                        "},"
                        "\"1002\":{"
                          "\"SoPhong\":5,"
                          "\"NguoiThue\":{"
                            "\"Ten\":\"Phan Hoang Trung\","
                            "\"CCCD\":\"012345678912\","
                            "\"Tuoi\":24,"
                            "\"ThuongTru\":{"
                              "\"Duong\":\"53 Le Dai Hanh\","
                              "\"Phuong_Xa\":\"Phuong 11\","
                              "\"Tinh_TP\":\"Ho Chi Minh\""
                            "}"
                          "},"
                          "\"SoNguoiO\":{"
                            "\"1\":\"Phan Van Nhat\","
                            "\"2\":\"Phan Van Nhi\","
                            "\"2\":\"Phan Van Tam\","
                            "\"3\":\"Phan Van Tu\""
                          "},"
                          "\"TienDien\":23.000,"
                          "\"TienNuoc\":40.000"
                        "}"
                      "}";
    

    // Phân tích cú pháp chuỗi JSON
    JsonValue* json_value = parse_json(&json_str);

   display(json_value);

    // Kiểm tra kết quả phân tích cú pháp

       // Giải phóng bộ nhớ được cấp phát cho JsonValue
    free_json_value(json_value);

        //printf("test = %x", '\"');

       // hienthi(5);
    
    return 0;
}