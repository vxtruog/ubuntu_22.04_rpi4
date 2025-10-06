# Một số lệnh cơ bản dùng trong CMakelists.txt trong ROS2
- Khai báo phiên bản cho dự án
```
cmake_minimum_required(VERSION x.xx)
```
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
add_executable(<CMAKE_PROJECT_NAME/EXEC_NAME> "<source_code>")
```
- Liên kết tệp thực thi với các tệp header trong dự án
```
target_include_directories(<CMAKE_PROJECT_NAME/EXEC_NAME> PUBLIC/PRIVATE "<include_link>")
```
- Thêm một tệp thư viện trong dự án, có source code để build
```
add_library(<library_name> STATIC/SHARED "<source_code>")
```
- Liên kết tệp thực thi với các tệp thư viện trong dự án
```
target_link_libraries(<CMAKE_PROJECT_NAME/EXEC_NAME> PUBLIC/PRIVATE "<library_name>")
```
- Mở rộng tệp thực thi hoặc tệp thư viện khi muốn thêm một tính năng mới
```
target_sources(<CMAKE_PROJECT_NAME/EXEC_NAME/LIBRARY_NAME> PUBLIC/PRIVATE "<source_code>")
```
- Sau khi hoàn thành thêm các tệp và liên kết, cài tệp thực thi và thư viện vào đúng vị trí trong workspace để ROS2 có thể tìm thấy và chạy được
```
- Cài tệp thực thi hoặc thư viện
install(TARGETS
  <CMAKE_PROJECT_NAME/EXEC_NAME/LIBRARY_NAME>
  DESTINATION lib/${PROJECT_NAME}
)

- Cài tệp header hoặc thư mục header
install(DIRECTORY
  <HEADER_FILE/INCLUDE_FOLDER>
  DESTINATION include
)

- Cài tệp config hoặc tệp launch
install(DIRECTORY
  launch/ config/
  DESTINATION share/${PROJECT_NAME}
)
```
- Tìm thư viện có sẵn trong hệ thống để liên kết
```
find_library(<var_library_name> <library_name> <library_path> REQUIRED)
<library_name> không cần tiền tố "lib" và phần đuôi mở rộng.
<library_path> chỉ cần khi dùng thư viện không nằm trong các thư mục hệ thống chuẩn.
```
- Tìm gói có sẵn trong hệ thống để liên kết
```
find_package(<package_name> REQUIRED COMPONENTS <component_name>)
```
# Sử dụng với những dự án hệ thống hơn
- Chạy tệp CMakelists.txt trong thư mục con để có tài nguyên dùng tại thư mục chính
```
add_subdirectory("<directory_link>")
```
- Liên kết thư viện trong thư mục Cmakelists.txt con với thư mục Cmakelists.txt chính
```
- Trong thư mục CMakelists.txt con:
  add_library()
  target_include_directories()
- Trong thư mục CMakelists.txt chính:
  add_subdirectory()
  target_link_libraries()
```
