- Khai báo dự án
```
project(<CMAKE_PROJECT_NAME>)
```
- Thêm một tệp thực thi trong dự án
```
add-executable(${CMAKE_PROJECT_NAME} "<source_code_name>")\
>> ${CMAKE_PROJECT_NAME} có thể thay bằng tên tệp thực thi bất kỳ
```
- Thiết lập chuẩn C++ cho dự án, ở đây dùng C++17
```
set(CMAKE_CXX_STANDARD 17)
```
