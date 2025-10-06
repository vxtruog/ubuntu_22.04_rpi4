# Một số lệnh cơ bản
- Khai báo dự án
```
project(<CMAKE_PROJECT_NAME>)
```
- Thiết lập chuẩn C++ cho dự án, ở đây dùng C++17
```
set(CMAKE_CXX_STANDARD 17)
```
- Thêm một tệp thực thi trong dự án
```
add_executable(<CMAKE_PROJECT_NAME/EXEC_NAME> "<source_code>")\
```
- Liên kết tệp thực thi với các tệp header trong dự án
```
target_include_directories(<CMAKE_PROJECT_NAME/EXEC_NAME> PUBLIC/PRIVATE "<include_link>")
```
- Thêm một tệp thư viện trong dự án
```
add_library(<library_name> STATIC/SHARED "<source_code>")
```
- Liên kết tệp thực thi với các tệp thư viện trong dự án
```
target_link_libraries(<CMAKE_PROJECT_NAME/EXEC_NAME> PUBLIC/PRIVATE "<library_name>")
```
# Sử dụng với những dự án hệ thống hơn
- Chạy tệp CMakelists.txt trong thư mục con để có tài nguyên dùng tại thư mục chính
```
add_subdirectory("<directory_link>")
```
- Liên kết thư viện trong thư mục Cmakelists.txt con với thư mục Cmakelists.txt chính
```
- Trong thư mục Cmakelists.txt con
  add_library(profilerLib INTERFACE)
  target_include_directories(profilerLib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
```
